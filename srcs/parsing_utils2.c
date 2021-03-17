/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:25:53 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/16 16:04:21 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_rgb(char **tab, t_pars *p)
{
	int i;
	int j;
	int nbr;

	nbr = 0;
	i = 0;
	while(tab[i])
		i++;
	if (i != 3)
		quit_prog("Error RGB format\n", p);
	i = -1;
	while(tab[++i])
	{
		j = -1;
		while(tab[i][++j])
			if (!ft_isdigit(tab[i][j]))
				quit_prog("Error RGB format\n", p);
		nbr = ft_atoi(tab[i]);
		if (nbr > 255 || nbr < 0)
			quit_prog("Error RGB format\n", p);
	}
	return (1);
}

int	check_resolution(char **tab, t_pars *p)
{
	int i;
	int j;
	int nbr;

	nbr = 0;
	i = 0;
	while(tab[i])
		i++;
	if (i != 2)
		quit_prog("Window resolution issue\n", p);
	i = -1;
	while(tab[++i])
	{
		j = -1;
		while(tab[i][++j])
			if (!ft_isdigit(tab[i][j]))
				quit_prog("Window resolution issue\n", p);
		nbr = ft_atoi(tab[i]);
		if (nbr < 0)
			quit_prog("Window resolution issue\n", p);
	}
	return (1);
}