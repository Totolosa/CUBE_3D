/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:58:59 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/15 11:45:58 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_print_sprite(int i, t_print_sprite *print, t_pars *p)
{
	print->x_scr = p->spr[i].l_scr;
	if (p->spr[i].h_scr > p->scr.h)
	{
		print->y_spr = (p->spr[i].h_scr - (double)p->scr.h) / 2
			/ p->spr[i].h_scr * (double)p->spr_text.h;
		print->y_scr = 0;
	}
	else
	{
		print->y_spr = 0;
		print->y_scr = (double)p->scr.h / 2 - p->spr[i].h_scr / 2;
	}
	return (1);
}

int	print_one_sprite(int i, t_print_sprite print, t_pars *p)
{
	while (print.y_spr < p->spr_text.h && print.y_scr < p->scr.h)
	{
		print.x_spr = 0;
		print.x_scr = p->spr[i].l_scr;
		while (print.x_scr < p->spr[i].r_scr && print.x_scr < p->scr.w)
		{
			if (print.x_scr >= 0 && p->spr_text.img[(int)print.x_spr
				+ ((int)print.y_spr * p->spr_text.s_l)] != p->spr_text.cont
				&& p->w_dst_col[(int)print.x_scr] > p->spr[i].dst)
			{
				p->scr.img[(int)print.x_scr + (int)print.y_scr * p->scr.s_l]
					= p->spr_text.img[(int)print.x_spr + ((int)print.y_spr
						* p->spr_text.s_l)];
			}
			print.x_spr += p->spr[i].scale_w;
			print.x_scr++;
		}
		print.y_spr += p->spr[i].scale_h;
		print.y_scr++;
	}
	return (1);
}

int	print_sprites(t_pars *p)
{
	int				i;
	t_print_sprite	print;

	i = -1;
	while (++i < p->nb_spr)
	{
		if (p->spr[i].l_scr < p->scr.w && p->spr[i].r_scr > 0
			&& p->spr[i].v_dir > 0 && p->spr[i].dst > 0)
		{
			init_print_sprite(i, &print, p);
			print_one_sprite(i, print, p);
		}
	}
	return (1);
}
