/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_v3_sprites_vector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:32:35 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/11 17:49:12 by tdayde           ###   ########lyon.fr   */
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
		pars->spr[i].x_dif = pars->spr[i].x - pars->moov.x_pos;
		pars->spr[i].y_dif = pars->spr[i].y - pars->moov.y_pos;
		pars->spr[i].v_dir = pars->spr[i].x_dif * pars->moov.x_dir
			+ pars->spr[i].y_dif * pars->moov.y_dir;
		pars->spr[i].v_per = pars->spr[i].x_dif * (-pars->moov.y_dir)
			+ pars->spr[i].y_dif * pars->moov.x_dir;
		pars->spr[i].dst = sqrt(pow(pars->spr[i].v_dir, 2)
			+ pow(pars->spr[i].v_per, 2));
		printf("sprite %d : v_dir = %f, v_per = %f, v_dst = %f\n", i+1, pars->spr[i].v_dir, pars->spr[i].v_per, pars->spr[i].dst);
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
