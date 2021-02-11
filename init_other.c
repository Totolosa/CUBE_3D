/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:42:09 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/11 15:15:41 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_t_ray(double angle, t_ray *ray)
{
	ray->wall.x = -1;
	ray->wall.y = -1;
	ray->wall.dst = INT_MAX;
	ray->wall.orient = 0;
	ray->angle = angle;
	ray->x_dir = cos(angle);
	ray->y_dir = sin(angle);
	ray->x_dir_per = -ray->y_dir;
	ray->y_dir_per = ray->x_dir;
	ray->w_scr_h = 0;
	ray->sky_h = 0;
	ray->line = 0;
}

// void	init_new_sprite(t_sprite *sprite)
// {
// 	sprite->x = 0;
// 	sprite->y = 0;
// 	sprite->v_x = 0;
// 	sprite->v_y = 0;
// 	sprite->dst = 0;
// }