/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_v3_sprites_vector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:32:35 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/10 17:06:22 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int calcul_distance_sprite(t_pars *pars)
{
	(void)pars;
	int i;

	i = -1;
	while (++i < pars->nb_spr)
	{
		pars->spr[i].v_x = pars->spr[i].x - pars->moov.x_pos;
		pars->spr[i].v_x = pars->spr[i].y - pars->moov.y_pos;
//		pars->spr[i].dst = pars->spr[i]v_x * cos()
	}
	return (1);
}

void modify_img(t_pars *pars)
{
	t_ray ray;
	int i;

	i = 0;
	init_t_ray((pars->moov.ang - (pars->scr.fov / 2)) / (180 / M_PI), &ray);
	while (i < pars->scr.w)
	{
	//	printf("angle = %f\n", ray.angle * (180 / M_PI));
		find_wall_contact(&ray, pars);
	//	printf("colonne = %d, nb_sprite = %d\n", count, ray.nb_sprites);
	//	printf("colonne = %d, wall.dst = %f\n", count, wall.dst);
		print_wall_col(&ray, i, pars);
		i++;
		init_t_ray((pars->moov.ang - (pars->scr.fov / 2)
		+ pars->moov.ang_pix * (i + 1)) / (180 / M_PI), &ray);
	}
	if (pars->nb_spr > 0)
	{
		calcul_distance_sprite(pars);
	}
}
