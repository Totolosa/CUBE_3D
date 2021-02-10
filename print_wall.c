/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:51:30 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/10 18:07:19 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calcul_scale_h(double *scale_h, t_ray *ray, t_pars *pars)
{
	if (ray->wall.orient == 'n')
		*scale_h = (double)pars->no.h / ray->w_scr_h;
	else if (ray->wall.orient == 's')
		*scale_h = (double)pars->so.h / ray->w_scr_h;
	else if (ray->wall.orient == 'w')
		*scale_h = (double)pars->we.h / ray->w_scr_h;
	else if (ray->wall.orient == 'e')
		*scale_h = (double)pars->ea.h / ray->w_scr_h;
	return (1);
}

int	calcul_x_text(double *x_text, t_ray *ray, t_pars *pars)
{
	double	scale_w;

	scale_w = 0;
	if (ray->wall.orient == 'n' || ray->wall.orient == 's')
		scale_w = modf(ray->wall.x, &scale_w);
	else if (ray->wall.orient == 'w' || ray->wall.orient == 'e')
		scale_w = modf(ray->wall.y, &scale_w);
	if (ray->wall.orient == 'n')
		*x_text = scale_w * (double)pars->no.w;
	else if (ray->wall.orient == 's')
		*x_text = scale_w * (double)pars->so.w;
	else if (ray->wall.orient == 'w')
		*x_text = scale_w * (double)pars->we.w;
	else if (ray->wall.orient == 'e')
		*x_text = scale_w * (double)pars->ea.w;
	return (1);
}

int	calcul_y_text(double *y_text, t_ray *ray, t_pars *pars)
{
	if (ray->wall.orient == 'n')
		*y_text = (ray->w_scr_h - (double)pars->scr.h) / 2
			/ ray->w_scr_h * (double)pars->no.h;
	else if (ray->wall.orient == 's')
		*y_text = (ray->w_scr_h - (double)pars->scr.h) / 2
			/ ray->w_scr_h * (double)pars->so.h;
	else if (ray->wall.orient == 'w')
		*y_text = (ray->w_scr_h - (double)pars->scr.h) / 2
			/ ray->w_scr_h * (double)pars->we.h;
	else if (ray->wall.orient == 'e')
		*y_text = (ray->w_scr_h - (double)pars->scr.h) / 2
			/ ray->w_scr_h * (double)pars->ea.h;
	ray->w_scr_h = pars->scr.h;
	return (1);
}

// int choose_text_wall(int *x, t_ray *ray, t_pars *pars)
// {
// 	if (ray->wall.orient == 'n')
// 		pars->scr.img[*x + ray->line * pars->scr.s_l]
// 			= pars->no.img[(int)x_text + ((int)y_text * pars->no.s_l)];
// 	else if (ray->wall.orient == 's')
// 		pars->scr.img[*x + ray->line * pars->scr.s_l]
// 			= pars->so.img[(int)x_text + ((int)y_text * pars->so.s_l)];
// 	else if (ray->wall.orient == 'w')
// 		pars->scr.img[*x + ray->line * pars->scr.s_l]
// 			= pars->we.img[(int)x_text + ((int)y_text * pars->we.s_l)];
// 	else if (ray->wall.orient == 'e')
// 		pars->scr.img[*x + ray->line * pars->scr.s_l]
// 			= pars->ea.img[(int)x_text + ((int)y_text * pars->ea.s_l)];
// 	return (1);
// }

int	print_wall_texture(int *x, t_ray *ray, t_pars *pars)
{
	double	scale_h;
	double	x_text;
	double	y_text;

	calcul_scale_h(&scale_h, ray, pars);
	calcul_x_text(&x_text, ray, pars);
	y_text = 0;
	if (ray->w_scr_h > pars->scr.h)
		calcul_y_text(&y_text, ray, pars);
	while (ray->line < ray->w_scr_h + ray->sky_h)
	{
		if (ray->wall.orient == 'n')
			pars->scr.img[*x + ray->line * pars->scr.s_l]
				= pars->no.img[(int)x_text + ((int)y_text * pars->no.s_l)];
		else if (ray->wall.orient == 's')
			pars->scr.img[*x + ray->line * pars->scr.s_l]
				= pars->so.img[(int)x_text + ((int)y_text * pars->so.s_l)];
		else if (ray->wall.orient == 'w')
			pars->scr.img[*x + ray->line * pars->scr.s_l]
				= pars->we.img[(int)x_text + ((int)y_text * pars->we.s_l)];
		else if (ray->wall.orient == 'e')
			pars->scr.img[*x + ray->line * pars->scr.s_l]
				= pars->ea.img[(int)x_text + ((int)y_text * pars->ea.s_l)];
		y_text += scale_h;
		ray->line++;
	}
	return (1);
}

int	print_wall_col(t_ray *ray, int x, t_pars *pars)
{
	ray->w_scr_h = (double)pars->scr.d / ray->wall.dst;
	if (ray->w_scr_h <= pars->scr.h)
		ray->sky_h = ((double)pars->scr.h - ray->w_scr_h) / 2;
	else
		ray->sky_h = 0;
	while (ray->line < ray->sky_h)
	{
		pars->scr.img[x + ray->line * pars->scr.s_l] = pars->sky_col;
		ray->line++;
	}
	print_wall_texture(&x, ray, pars);
	while (ray->line < pars->scr.h)
	{
		pars->scr.img[x + ray->line * pars->scr.s_l] = pars->floor_col;
		ray->line++;
	}
	return (1);
}
