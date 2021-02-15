/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:47:17 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/15 10:57:18 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cpy_spr_to_tmp(int i, t_sprite *tmp, t_pars *pars)
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

int	cpy_spr_to_spr(int i, t_pars *pars)
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

int	cpy_tmp_to_spr(int i, t_sprite *tmp, t_pars *pars)
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

int	order_sprite(t_pars *pars)
{
	int			i;
	int			j;
	t_sprite	tmp;

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

int	calcul_h_sprite(t_pars *p)
{
	int	i;

	i = -1;
	while (++i < p->nb_spr)
	{
		p->spr[i].x_dif = p->spr[i].x - p->moov.x_pos;
		p->spr[i].y_dif = p->spr[i].y - p->moov.y_pos;
		p->spr[i].v_dir = p->spr[i].x_dif * p->moov.x_dir
			+ p->spr[i].y_dif * p->moov.y_dir;
		p->spr[i].v_per = p->spr[i].x_dif * (-p->moov.y_dir)
			+ p->spr[i].y_dif * p->moov.x_dir;
		p->spr[i].dst = sqrt(pow(p->spr[i].v_dir, 2) + pow(p->spr[i].v_per, 2));
		p->spr[i].dst_scr = p->scr.d / p->spr[i].v_dir * p->spr[i].dst ;
		p->spr[i].cen_scr = (p->scr.d / p->spr[i].v_dir * p->spr[i].v_per)
			+ (double)p->scr.w / 2;
		p->spr[i].w_scr = 0.5 * p->spr[i].dst_scr / p->spr[i].dst;
		p->spr[i].r_scr = p->spr[i].cen_scr + p->spr[i].w_scr;
		p->spr[i].l_scr = p->spr[i].cen_scr - p->spr[i].w_scr;
		p->spr[i].h_scr = (double)p->scr.d / p->spr[i].dst;
		p->spr[i].scale_h = p->spr_text.h / p->spr[i].h_scr;
		p->spr[i].scale_w = p->spr_text.w / (p->spr[i].w_scr * 2);
	}
	order_sprite(p);
	return (1);
}
