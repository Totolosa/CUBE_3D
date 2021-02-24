/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:43:44 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/23 15:46:48 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite	*add_sprite(int y, int x, t_pars *pars)
{
	t_sprite	*new;
	int			i;

	new = ft_alloc(sizeof(t_sprite) * (pars->nb_spr + 1), pars->free);
	i = -1;
	while (++i < pars->nb_spr)
		new[i] = pars->spr[i];
	new[i].x = (double)x + 0.5;
	new[i].y = (double)y + 0.5;
	new[i].x_dif = 0;
	new[i].y_dif = 0;
	new[i].v_dir = 0;
	new[i].v_per = 0;
	new[i].dst = 0;
	free(pars->spr);
	pars->nb_spr++;
	return (new);
}

int	init_position(char c, int i, int j, t_pars *pars)
{
	pars->moov.x_pos = j + 0.5;
	pars->moov.y_pos = i + 0.5;
	if (c == 'N')
		pars->moov.ang = -90;
	if (c == 'S')
		pars->moov.ang = 90;
	if (c == 'W')
		pars->moov.ang = 180;
	if (c == 'E')
		pars->moov.ang = 0;
	pars->moov.x_dir = cos(pars->moov.ang / (180 / M_PI));
	pars->moov.y_dir = sin(pars->moov.ang / (180 / M_PI));
	pars->map.map[i][j] = (int)c;
	return (1);
}

int	fill_line_map(int i, char *line, t_pars *pars)
{
	int	j;
	int	k;

	k = -1;
	j = 0;
	while (line[++k])
	{
		if (line[k] != ' ')
			pars->map.map[i][j] = line[k] - '0';
		if (line[k] == '2')
			pars->spr = add_sprite(i, j, pars);
		if (line[k] == 'N' || line[k] == 'S' || line[k] == 'W'
			|| line[k] == 'E')
			init_position(line[k], i, j, pars);
		j++;
	}
	return (1);
}

static int	map_browse_file(int *ret, char **line, int fd, t_pars *pars)
{
	int	i;

	i = 0;
	while (((*line)[0] == ' ' || (*line)[0] == '1'
			|| (*line)[0] == '2') && *ret > 0)
	{
		fill_line_map(i, *line, pars);
		i++;
		free(*line);
		*ret = get_next_line(fd, line);
	}
	if (*ret == -1)
	{
		free(*line);
		quit_prog("GNL failded\n", pars);
	}
	fill_line_map(i, *line, pars);
	free(*line);
	return (1);
}

int	fill_map(t_pars *pars)
{
	int		ret;
	char	*line;
	int		fd;

	ret = 0;
	line = NULL;
	fd = open(pars->map.map_file, O_RDONLY);
	if (fd == -1)
		quit_prog("fct open() fill_map.c failded\n", pars);
	start_browse_file(&ret, &line, fd, pars);
	map_browse_file(&ret, &line, fd, pars);
	close(fd);
	return (1);
}
