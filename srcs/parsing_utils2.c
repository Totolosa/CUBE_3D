/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:25:53 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/19 14:32:51 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_rgb(char *line, t_pars *p)
{
	int	nbr;
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (!ft_isdigit(*line))
			quit_prog("Error RGB format\n", p);
		nbr = ft_atoi_cub(line);
		if (nbr > 255 || nbr < 0)
			quit_prog("Error RGB format\n", p);
		while (ft_isdigit(*line))
			line++;
		if (i != 2 && *line != ',')
			quit_prog("Error RGB format\n", p);
		if (i == 2 && *line != '\0')
			quit_prog("Error RGB format\n", p);
		if (i != 2)
			line++;
	}
	return (1);
}

int	check_resolution(char **tab, t_pars *p)
{
	int	i;
	int	j;
	int	nbr;

	nbr = 0;
	i = 0;
	while (tab[i])
		i++;
	if (i != 2)
		quit_prog("Window resolution issue\n", p);
	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			if (!ft_isdigit(tab[i][j]))
				quit_prog("Window resolution issue\n", p);
		nbr = ft_atoi_cub(tab[i]);
		if (nbr < 0)
			quit_prog("Window resolution issue\n", p);
	}
	return (1);
}

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

int	end_parsing_first_part(int fd, int ret, char **line, t_pars *pars)
{
	while (ret > 0)
	{
		free_obj((void **)line);
		ret = get_next_line(fd, line);
	}
	if (ret == -1)
	{
		free_obj((void **)line);
		quit_prog("GNL failed\n", pars);
	}
	free_obj((void **)line);
	return (1);
}
