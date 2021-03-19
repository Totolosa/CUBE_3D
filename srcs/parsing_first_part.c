/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_first_part.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:42:39 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/19 12:41:49 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	assign_resolution(char *line, t_pars *p)
{
	char	*resolution;
	char	**tab;

	resolution = ft_strtrim_cub(line, "RNOSWEA \n", p);
	tab = ft_split_cub(resolution, ' ', p);
	check_resolution(tab, p);
	p->scr.w = ft_atoi_cub(tab[0]);
	p->scr.h = ft_atoi_cub(tab[1]);
	p->declaration.res++;
	return (1);
}

static int	assign_color(char *line, t_pars *pars)
{
	char	**tab;
	char	c;
	int		red;
	int		green;
	int		blue;

	c = line[0];
	line = ft_strtrim_cub(line, "FC \n", pars);
	check_rgb(line, pars);
	tab = ft_split_cub(line, ',', pars);
	red = ft_atoi_cub(tab[0]);
	green = ft_atoi_cub(tab[1]);
	blue = ft_atoi_cub(tab[2]);
	if (c == 'C')
		pars->sky_col = red * 256 * 256 + green * 256 + blue;
	if (c == 'F')
	{
		pars->floor_col = red * 256 * 256 + green * 256 + blue;
		pars->declaration.floor++;
	}
	return (1);
}

static int	assign_sky(char *line, t_pars *pars)
{
	char	*tmp;

	tmp = ft_strtrim_cub(line, "C \n", pars);
	if (ft_isdigit(tmp[0]))
		assign_color(line, pars);
	else
		pars->sky_text.path = ft_strtrim_cub(line, "C \n", pars);
	pars->declaration.sky++;
	return (1);
}

int	reconize_line(char *line, t_pars *pars)
{
	if (line[0] == '\0')
		return (1);
	else if (line[0] == 'R' && line[1] == ' ')
		assign_resolution(line, pars);
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		assign_text(&pars->no.path, "NO \n", line, pars);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		assign_text(&pars->so.path, "SO \n", line, pars);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		assign_text(&pars->we.path, "WE \n", line, pars);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		assign_text(&pars->ea.path, "EA \n", line, pars);
	else if (line[0] == 'S' && line[1] == ' ')
		assign_text(&pars->spr_text.path, "S \n", line, pars);
	else if (line[0] == 'C' && line[1] == ' ')
		assign_sky(line, pars);
	else if (line[0] == 'F' && line[1] == ' ')
		assign_color(line, pars);
	else
		quit_prog("Line Incorect\n", pars);
	return (1);
}

int	parsing_first_part(char *file, t_pars *pars)
{
	int		ret;
	char	*l;
	int		fd;

	l = NULL;
	ret = 0;
	check_file_name(file, pars);
	fd = open(pars->map.map_file, O_RDONLY);
	if (fd == -1)
		quit_prog("File do not exist or his name is incorrect\n", pars);
	ret = get_next_line(fd, &l);
	while (ret > 0 && l[0] != ' ' && l[0] != '0' && l[0] != '1' && l[0] != '2')
	{
		reconize_line(l, pars);
		free_obj((void **)&l);
		ret = get_next_line(fd, &l);
	}
	end_parsing_first_part(fd, ret, &l, pars);
	check_declaration(pars);
	close(fd);
	return (1);
}
