/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:56:25 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/16 15:32:56 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void printf_info_map(t_pars *pars)
{
	int i = -1, j = -1;
	
	while (++i < pars->map.map_h)
	{
		j = -1;
		while (++j < pars->map.map_w)
		{
			if (pars->map.map[i][j] == -1)
				printf(" ");
			else
				printf("%d", pars->map.map[i][j]);
		}
		printf("\n");
	}
	printf("map_w = %d, map_h = %d\n", pars->map.map_w, pars->map.map_h);
	i = -1;
	while (++i < pars->nb_spr)
		printf("sprite %d : x = %f, y = %f\n", i + 1, pars->spr[i].x, pars->spr[i].y);
	printf("nb_spr = %d\n", pars->nb_spr);
}

int parsing(t_pars *pars, char *file)
{
	pars->map.map_file = file;
	parsing_first_part(pars);
	create_window_textures(pars);
	parsing_map(pars);
	printf_info_map(pars);
	return (1);
}