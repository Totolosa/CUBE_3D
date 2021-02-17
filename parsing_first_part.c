/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_first_part.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:42:39 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/17 18:00:12 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	assign_resolution(char *line, t_pars *p)
{
	char	*resolution;
	char	**tab;

	resolution = ft_strtrim_cub(line, "RNOSWEA \n", p);
	tab = ft_split_cub(resolution, ' ', p);
	p->scr.w = ft_atoi(tab[0]);
	p->scr.h = ft_atoi(tab[1]);
	return (1);
}

int	assign_color_sky_floor(char *line, t_pars *pars)
{
	char	**tab;
	char	c;
	int		red;
	int		green;
	int		blue;

	c = line[0];
	line = ft_strtrim_cub(line, "RNOSWEA \n", pars);
	tab = ft_split_cub(line, ',', pars);
	red = ft_atoi(tab[0]);
	green = ft_atoi(tab[1]);
	blue = ft_atoi(tab[2]);
	if (c == 'F')
		pars->sky_col = red * 256 * 256 + green * 256 + blue;
	if (c == 'C')
		pars->floor_col = red * 256 * 256 + green * 256 + blue;
	return (1);
}

int reconize_line(char *line, t_pars *pars)
{
	if (line[0] == 'R' && line[1] == ' ')
		assign_resolution(line, pars);
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		pars->no.path = ft_strtrim_cub(line, "RNOSWEA \n", pars);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		pars->so.path = ft_strtrim_cub(line, "RNOSWEA \n", pars);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		pars->we.path = ft_strtrim_cub(line, "RNOSWEA \n", pars);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		pars->ea.path = ft_strtrim_cub(line, "RNOSWEA \n", pars);
	else if (line[0] == 'S' && line[1] == ' ')
		pars->spr_text.path = ft_strtrim_cub(line, "RNOSWEA \n", pars);
	else if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
		assign_color_sky_floor(line, pars);
	return (1);
}

int	parsing_first_part(t_pars *pars)
{
	int		ret;
	char	*line;
	int		fd;

	line = NULL;
	ret = 0;
	fd = open(pars->map.map_file, O_RDONLY);
	if (fd == -1)
		quit_prog(pars);
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		reconize_line(line, pars);
		free(line);
		ret = get_next_line(fd, &line);
	}
	if (ret == -1)
	{
		free(line);
		quit_prog(pars);
	}
	close(fd);
	return (1);
}
