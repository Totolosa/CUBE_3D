/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:16:59 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/18 16:53:42 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	start_browse_file(int *ret, char **line, int fd, t_pars *pars)
{
	*ret = get_next_line(fd, line);
	while (*line[0] != ' ' && *line[0] != '1' && *line[0] != '2' && *ret > 0)
	{
		free(*line);
		*ret = get_next_line(fd, line);
	}
	if (*ret == -1 || *ret == 0)
	{
		free(*line);
		quit_prog(pars);
	}
	return (1);
}

static int	map_browse_file(int *ret, char **line, int fd, t_pars *pars)
{
	int	i;
	int	count_w;

	while (((*line)[0] == ' ' || (*line)[0] == '1'
			|| (*line)[0] == '2') && *ret > 0)
	{
		if ((*line)[0] == '\0')
		{
			free(*line);
			quit_prog(pars);
		}
		i = -1;
		count_w = 0;
		while ((*line)[++i])
			if (pars->map.map_w < ++count_w)
				pars->map.map_w++;
		pars->map.map_h++;
		free(*line);
		*ret = get_next_line(fd, line);
	}
	if ((*line)[0] == ' ' || (*line)[0] == '1' || (*line)[0] == '2')
		pars->map.map_h++;
	return (1);
}

int	end_browse_file(int *ret, char **line, int fd, t_pars *pars)
{
	while ((*line)[0] == '\0' && *ret > 0)
	{
		free(*line);
		*ret = get_next_line(fd, line);
		if ((*line)[0] != '\0')
		{
			free(*line);
			quit_prog(pars);
		}
	}
	if (*ret == -1)
	{
		free(*line);
		quit_prog(pars);
	}
	free(*line);
	return (1);
}

int	reconize_size_map(t_pars *pars)
{
	int		ret;
	char	*line;
	int		fd;

	ret = 0;
	line = NULL;
	fd = open(pars->map.map_file, O_RDONLY);
	if (fd == -1)
		quit_prog(pars);
	start_browse_file(&ret, &line, fd, pars);
	map_browse_file(&ret, &line, fd, pars);
	if (ret == -1)
	{
		free(line);
		quit_prog(pars);
	}
	end_browse_file(&ret, &line, fd, pars);
	close(fd);
	return (1);
}

int	create_map(t_pars *pars, int c)
{
	int	i;
	int	j;

	reconize_size_map(pars);
	pars->map.map = ft_alloc(sizeof(int*) * pars->map.map_h, pars->free);
	i = -1;
	while (++i < pars->map.map_h)
		pars->map.map[i] = ft_alloc(sizeof(int) * pars->map.map_w, pars->free);
	i = -1;
	while (++i < pars->map.map_h)
	{
		j = -1;
		while (++j < pars->map.map_w)
			pars->map.map[i][j] = c;
	}
	return (1);
}
