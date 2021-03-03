/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:51:30 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/03 12:29:41 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calcul_x_text(t_print_text *text, t_ray *ray, t_pars *pars)
{
	double	scale_w;

	scale_w = 0;
	if (ray->wall.orient == 'n' || ray->wall.orient == 's')
		scale_w = modf(ray->wall.x, &scale_w);
	else if (ray->wall.orient == 'w' || ray->wall.orient == 'e')
		scale_w = modf(ray->wall.y, &scale_w);
	if (ray->wall.orient == 'n')
		text->x = scale_w * (double)pars->no.w;
	else if (ray->wall.orient == 's')
		text->x = scale_w * (double)pars->so.w;
	else if (ray->wall.orient == 'w')
		text->x = scale_w * (double)pars->we.w;
	else if (ray->wall.orient == 'e')
		text->x = scale_w * (double)pars->ea.w;
	return (1);
}

int	calcul_y_text(t_print_text *text, t_ray *ray, t_pars *pars)
{
	if (ray->wall.orient == 'n')
		text->y = (ray->w_scr_h - (double)pars->scr.h) / 2
			/ ray->w_scr_h * (double)pars->no.h;
	else if (ray->wall.orient == 's')
		text->y = (ray->w_scr_h - (double)pars->scr.h) / 2
			/ ray->w_scr_h * (double)pars->so.h;
	else if (ray->wall.orient == 'w')
		text->y = (ray->w_scr_h - (double)pars->scr.h) / 2
			/ ray->w_scr_h * (double)pars->we.h;
	else if (ray->wall.orient == 'e')
		text->y = (ray->w_scr_h - (double)pars->scr.h) / 2
			/ ray->w_scr_h * (double)pars->ea.h;
	ray->w_scr_h = pars->scr.h;
	return (1);
}

int	calcul_info_text(t_print_text *text, t_ray *ray, t_pars *pars)
{
	init_print_text(text);
	if (ray->wall.orient == 'n')
		text->scale_h = (double)pars->no.h / ray->w_scr_h;
	else if (ray->wall.orient == 's')
		text->scale_h = (double)pars->so.h / ray->w_scr_h;
	else if (ray->wall.orient == 'w')
		text->scale_h = (double)pars->we.h / ray->w_scr_h;
	else if (ray->wall.orient == 'e')
		text->scale_h = (double)pars->ea.h / ray->w_scr_h;
	calcul_x_text(text, ray, pars);
	if (ray->w_scr_h > pars->scr.h)
		calcul_y_text(text, ray, pars);
	return (1);
}

int	print_wall_texture(int *x, t_ray *ray, t_pars *pars)
{
	t_print_text	text;

	calcul_info_text(&text, ray, pars);
	while (ray->line < ray->w_scr_h + ray->sky_h)
	{
		if (ray->wall.orient == 'n')
			pars->scr.img[*x + ray->line * pars->scr.s_l]
				= pars->no.img[(int)text.x + ((int)text.y * pars->no.s_l)];
		else if (ray->wall.orient == 's')
			pars->scr.img[*x + ray->line * pars->scr.s_l]
				= pars->so.img[(int)text.x + ((int)text.y * pars->so.s_l)];
		else if (ray->wall.orient == 'w')
			pars->scr.img[*x + ray->line * pars->scr.s_l]
				= pars->we.img[(int)text.x + ((int)text.y * pars->we.s_l)];
		else if (ray->wall.orient == 'e')
			pars->scr.img[*x + ray->line * pars->scr.s_l]
				= pars->ea.img[(int)text.x + ((int)text.y * pars->ea.s_l)];
		text.y += text.scale_h;
		ray->line++;
	}
	return (1);
}

int	print_wall_col(t_ray *ray, int x_scr, t_pars *pars)
{
	ray->w_scr_h = pars->scr.d / ray->wall.dst;
	if (ray->w_scr_h <= pars->scr.h)
		ray->sky_h = ((double)pars->scr.h - ray->w_scr_h) / 2;
	else
		ray->sky_h = 0;
	print_sky(&x_scr, ray, pars);
	print_wall_texture(&x_scr, ray, pars);
	while (ray->line < pars->scr.h)
	{
		pars->scr.img[x_scr + ray->line * pars->scr.s_l] = pars->floor_col;
		ray->line++;
	}
	return (1);
}
