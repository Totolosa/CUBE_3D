/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:21:15 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/17 17:44:08 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_char(int c, int i, int j, t_pars *pars)
{
	static int position;
	
	if (c != -1 && c != 0 && c != 1 && c != 2
			&& c != 'N' && c != 'S' && c != 'W' && c != 'E')
		quit_prog(pars);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		position++;
	if (position == 2
			|| (i == pars->map.map_h && j == pars->map.map_w && position == 0))
		quit_prog(pars);
	return (1);
}

int check_map(t_pars *pars)
{
	int i;
	int j;

	i = -1;
	while (++i < pars->map.map_h)
	{
		j = -1;
		while (++j < pars->map.map_w)
			check_char(pars->map.map[i][j], i + 1, j + 1, pars);
	}
	return (1);
}

int parsing_map(t_pars *pars)
{
//	printf("map.w = %d, map_h = %d\n", pars->map.map_w, pars->map.map_h);
	create_map(pars, -1);
	fill_map(pars);
	if (!check_map(pars))
		quit_prog(pars);
	return (1);
}