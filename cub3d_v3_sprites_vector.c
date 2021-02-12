/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_v3_sprites_vector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:32:35 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/12 17:55:30 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int cpy_spr_to_tmp(int i, t_sprite *tmp, t_pars *pars)
{
	tmp->x = pars->spr[i].x;
	tmp->y = pars->spr[i].y;
	tmp->x_dif = pars->spr[i].x_dif;
	tmp->y_dif = pars->spr[i].y_dif;
	tmp->v_dir = pars->spr[i].v_dir;
	tmp->v_per = pars->spr[i].v_per;
	tmp->dst = pars->spr[i].dst;
	tmp->cen_scr = pars->spr[i].cen_scr;
	tmp->r_scr = pars->spr[i].r_scr;
	tmp->l_scr = pars->spr[i].l_scr;
	tmp->dst_scr = pars->spr[i].dst_scr;
	tmp->w_scr = pars->spr[i].w_scr;
	tmp->h_scr = pars->spr[i].h_scr;
	tmp->scale_h = pars->spr[i].scale_h;
	tmp->scale_w = pars->spr[i].scale_w;
	return (1);
}

int cpy_spr_to_spr(int i, t_pars *pars)
{
	pars->spr[i].x = pars->spr[i + 1].x;
	pars->spr[i].y = pars->spr[i + 1].y;
	pars->spr[i].x_dif = pars->spr[i + 1].x_dif;
	pars->spr[i].y_dif = pars->spr[i + 1].y_dif;
	pars->spr[i].v_dir = pars->spr[i + 1].v_dir;
	pars->spr[i].v_per = pars->spr[i + 1].v_per;
	pars->spr[i].dst = pars->spr[i + 1].dst;
	pars->spr[i].cen_scr = pars->spr[i + 1].cen_scr;
	pars->spr[i].r_scr = pars->spr[i + 1].r_scr;
	pars->spr[i].l_scr = pars->spr[i + 1].l_scr;
	pars->spr[i].dst_scr = pars->spr[i + 1].dst_scr;
	pars->spr[i].w_scr = pars->spr[i + 1].w_scr;
	pars->spr[i].h_scr = pars->spr[i + 1].h_scr;
	pars->spr[i].scale_h = pars->spr[i + 1].scale_h;
	pars->spr[i].scale_w = pars->spr[i + 1].scale_w;
	return (1);
}

int cpy_tmp_to_spr(int i, t_sprite *tmp, t_pars *pars)
{
	pars->spr[i].x = tmp->x;
	pars->spr[i].y = tmp->y;
	pars->spr[i].x_dif = tmp->x_dif;
	pars->spr[i].y_dif = tmp->y_dif;
	pars->spr[i].v_dir = tmp->v_dir;
	pars->spr[i].v_per = tmp->v_per;
	pars->spr[i].dst = tmp->dst;
	pars->spr[i].cen_scr = tmp->cen_scr;
	pars->spr[i].r_scr = tmp->r_scr;
	pars->spr[i].l_scr = tmp->l_scr;
	pars->spr[i].dst_scr = tmp->dst_scr;
	pars->spr[i].w_scr = tmp->w_scr;
	pars->spr[i].h_scr = tmp->h_scr;
	pars->spr[i].scale_h = tmp->scale_h;
	pars->spr[i].scale_w = tmp->scale_w;
	return (1);
}

int order_sprite(t_pars *pars)
{
	int i;
	int j;
	t_sprite tmp;

	j = -1;
	while (++j < pars->nb_spr - 1)
	{
		i = -1;
		while (++i < pars->nb_spr - 1)
		{
			if (pars->spr[i].v_dir < pars->spr[i + 1].v_dir)
			{
				cpy_spr_to_tmp(i, &tmp, pars);
				cpy_spr_to_spr(i, pars);
				cpy_tmp_to_spr(i + 1, &tmp, pars);
			}
		}
	}
	return (1);
}

int calcul_h_sprite(t_pars *pars)
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
		if (pars->spr[i].v_dir > 0 && pars->spr[i].dst > 0)
		{
			pars->spr[i].dst_scr = pars->scr.d / pars->spr[i].v_dir * pars->spr[i].dst ;
			pars->spr[i].cen_scr = (pars->scr.d / pars->spr[i].v_dir * pars->spr[i].v_per) + (double)pars->scr.w / 2;
			pars->spr[i].w_scr = 0.5 * pars->spr[i].dst_scr / pars->spr[i].dst;
			pars->spr[i].r_scr = pars->spr[i].cen_scr + pars->spr[i].w_scr;
			pars->spr[i].l_scr = pars->spr[i].cen_scr - pars->spr[i].w_scr;
			if (pars->spr[i].l_scr < pars->scr.w && pars->spr[i].r_scr > 0)
			{
				pars->spr[i].h_scr = pars->spr[i].dst_scr / pars->spr[i].dst;
				pars->spr[i].scale_h = pars->spr_text.h / pars->spr[i].h_scr;
				pars->spr[i].scale_w = pars->spr_text.w / (pars->spr[i].w_scr * 2);
			}
		}
		printf("sprite %d : v_dir = %.2f, v_per = %.2f, dst = %.2f, dst_scr = %.2f, cen_scr = %.2f, w_scr = %.2f, r_scr = %.2f, l_scr = %.2f, h_scr = %.2f, scale_h = %.4f, scale_w = %.4f\n",
		i+1, pars->spr[i].v_dir, pars->spr[i].v_per, pars->spr[i].dst, pars->spr[i].dst_scr, pars->spr[i].cen_scr, pars->spr[i].w_scr, pars->spr[i].r_scr, pars->spr[i].l_scr, pars->spr[i].h_scr, pars->spr[i].scale_h, pars->spr[i].scale_w);
	}
	order_sprite(pars);
	return (1);
}

int print_sprite(t_pars *pars)
{
	int i;
	double x_scr;
	double y_scr;
	double x_spr;
	double y_spr;
	
	i = -1;
	x_scr = 0;
	y_scr = 0;
	x_spr = 0;
	y_spr = 0;
	while (++i < pars->nb_spr)
	{
		if (pars->spr[i].l_scr < pars->scr.w && pars->spr[i].r_scr > 0 && pars->spr[i].v_dir > 0 && pars->spr[i].dst > 0)
		{
			x_scr = pars->spr[i].l_scr;
			y_scr = (double)pars->scr.h / 2 - (double)pars->spr[i].h_scr / 2;
			
			while (y_spr < pars->spr_text.h)
			{
				x_spr = 0;
				x_scr = pars->spr[i].l_scr;
				while (x_scr < pars->spr[i].r_scr)
				{
					if (x_scr >= 0 && pars->spr_text.img[(int)x_spr + ((int)y_spr * pars->spr_text.s_l)] != pars->spr_text.contour)
					{
					//	printf("spr_text.img = %d, pars->spr_text.contour = %d\n", pars->spr_text.img[(int)x_spr + ((int)y_spr * pars->spr_text.s_l)], pars->spr_text.contour);
						pars->scr.img[(int)x_scr + (int)y_scr * pars->scr.s_l] = pars->spr_text.img[(int)x_spr + ((int)y_spr * pars->spr_text.s_l)];

					}
					x_spr += pars->spr[i].scale_w;
					x_scr++;
				}
				y_spr += pars->spr[i].scale_h;
				y_scr++;
			}
		}
		printf("i = %d, nb_spr = %d\n", i, pars->nb_spr);
	}
	return (1);
}

// A FAIRE 
// - trier les sprites par distance
// - prendre en compte lorsque sprite trop pres (taille sprite ecran > taille ecran)
// - gerer lorsque un sprite derriere un mur

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
		calcul_h_sprite(pars);
		print_sprite(pars);
	}
}
