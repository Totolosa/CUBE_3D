/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_first_part.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:42:39 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/12 12:43:37 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_name(char *file, t_pars *pars)
{
	unsigned int	len;

	len = ft_strlen(file) - 1;
	if (file[len] != 'b')
		quit_prog("Error file name\n", pars);
	if (file[len - 1] != 'u')
		quit_prog("Error file name\n", pars);
	if (file[len - 2] != 'c')
		quit_prog("Error file name\n", pars);
	if (file[len - 3] != '.')
		quit_prog("Error file name\n", pars);
	pars->map.map_file = file;
	return (1);
}

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
	line = ft_strtrim_cub(line, "FC \n", pars);
	tab = ft_split_cub(line, ',', pars);
	red = ft_atoi(tab[0]);
	green = ft_atoi(tab[1]);
	blue = ft_atoi(tab[2]);
	if (c == 'C')
		pars->sky_col = red * 256 * 256 + green * 256 + blue;
	if (c == 'F')
		pars->floor_col = red * 256 * 256 + green * 256 + blue;
	return (1);
}

int	reconize_line(char *line, t_pars *pars)
{
	char	*tmp;

	if (line[0] == 'R' && line[1] == ' ')
		assign_resolution(line, pars);
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		pars->no.path = ft_strtrim_cub(line, "NO \n", pars);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		pars->so.path = ft_strtrim_cub(line, "SO \n", pars);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		pars->we.path = ft_strtrim_cub(line, "WE \n", pars);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		pars->ea.path = ft_strtrim_cub(line, "EA \n", pars);
	else if (line[0] == 'S' && line[1] == ' ')
		pars->spr_text.path = ft_strtrim_cub(line, "S \n", pars);
	else if (line[0] == 'C' && line[1] == ' ')
	{
		tmp = ft_strtrim_cub(line, "C \n", pars);
		if (ft_isdigit(tmp[ft_strlen(tmp) - 1]))
			assign_color_sky_floor(line, pars);
		else
			pars->sky_text.path = ft_strtrim_cub(line, "C \n", pars);
	}
	else if (line[0] == 'F' && line[1] == ' ')
		assign_color_sky_floor(line, pars);
	return (1);
}

int	parsing_first_part(char *file, t_pars *pars)
{
	int		ret;
	char	*line;
	int		fd;

	line = NULL;
	ret = 0;
	check_file_name(file, pars);
	fd = open(pars->map.map_file, O_RDONLY);
	if (fd == -1)
		quit_prog("File do not exist or his name is incorrect\n", pars);
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		reconize_line(line, pars);
		free_obj((void **)&line);
		ret = get_next_line(fd, &line);
	}
	if (ret == -1)
	{
		free_obj((void **)&line);
		quit_prog("GNL failed\n", pars);
	}
	free_obj((void **)&line);
	close(fd);
	return (1);
}
