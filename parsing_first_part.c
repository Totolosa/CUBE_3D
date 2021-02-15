/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_first_part.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:42:39 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/15 18:16:59 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	assign_resolution(char *line, t_pars *pars)
{
	char	*resolution;
	char	**tab;

	resolution = ft_strtrim_cub(line, "RNOSWEA \n", pars);
	tab = ft_split_cub(resolution, ' ', pars);
	pars->scr.w = ft_atoi(tab[0]);
	pars->scr.h = ft_atoi(tab[1]);
	pars->w_dst_col = ft_alloc(sizeof(double) * pars->scr.w, pars->free);
	pars->moov.ang_pix = pars->scr.fov / (double)pars->scr.w;
	pars->scr.d = ((double)pars->scr.w / 2)
		/ tan((pars->scr.fov / 2) / (180 / M_PI));
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

int	parsing_first_part(t_pars *pars)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open(pars->map.map_file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'R')
			assign_resolution(line, pars);
		else if (line[0] == 'N')
			pars->no.path = ft_strtrim_cub(line, "RNOSWEA \n", pars);
		else if (line[0] == 'S' && line[1] == 'O')
			pars->so.path = ft_strtrim_cub(line, "RNOSWEA \n", pars);
		else if (line[0] == 'W')
			pars->we.path = ft_strtrim_cub(line, "RNOSWEA \n", pars);
		else if (line[0] == 'E')
			pars->ea.path = ft_strtrim_cub(line, "RNOSWEA \n", pars);
		else if (line[0] == 'S' && line[1] == ' ')
			pars->spr_text.path = ft_strtrim_cub(line, "RNOSWEA \n", pars);
		else if (line[0] == 'F' || line[0] == 'C')
			assign_color_sky_floor(line, pars);
	}
	close(fd);
	return (1);
}
