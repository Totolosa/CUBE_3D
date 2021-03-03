/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sky.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:21:50 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/03 12:32:03 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_sky(int *x_scr, t_ray *ray, t_pars *pars)
{
	double	x_sky;
	double	y_sky;
	double	angle;
	double	scale_h;

	scale_h = (double)pars->sky_text.h / (double)pars->scr.h;
	angle = (ray->angle * (180 / M_PI));
	angle = fmod(angle, 180);
	x_sky = fabs(angle) / 180 * pars->sky_text.w;
	y_sky = 200;
	while (ray->line < ray->sky_h)
	{
		pars->scr.img[*x_scr + ray->line * pars->scr.s_l]
			= pars->sky_text.img[(int)x_sky + (int)y_sky * pars->sky_text.s_l];
		ray->line++;
		y_sky += scale_h / 2;
	}
	return (1);
}
