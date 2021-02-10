/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:53:16 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/10 16:56:17 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int continue_ray_horiz(double x, int y, t_ray *horiz, t_pars *pars)
{
	if ((x >= 1 && x < pars->map.map_w && y >= 1 && y < pars->map.map_h)
		&& ((horiz->y_dir > 0 && pars->map.map[y][(int)x] != -1)
				|| (horiz->y_dir < 0 && pars->map.map[y - 1][(int)x] != -1)))
		return (1);
	else 
		return (0);
}

int continue_ray_verti(int x, double y, t_ray *verti, t_pars *pars)
{
	if ((x >= 1 && x < pars->map.map_w && y >= 1 && y < pars->map.map_h)
		&& ((verti->x_dir > 0 && pars->map.map[(int)y][x] != -1)
				|| (verti->x_dir < 0 && pars->map.map[(int)y][x - 1] != -1)))
		return (1);
	else 
		return (0);
}

int horiz_or_verti(t_ray *ray, t_ray horiz, t_ray verti)
{
	if (horiz.wall.dst <= verti.wall.dst)
	{
		ray->wall.dst = horiz.wall.dst;
		ray->wall.x = horiz.wall.x;
		ray->wall.y = horiz.wall.y;
		ray->wall.orient = horiz.wall.orient;
	}
	else
	{
		ray->wall.dst = verti.wall.dst;
		ray->wall.x = verti.wall.x;
		ray->wall.y = verti.wall.y;
		ray->wall.orient = verti.wall.orient;
	}
	return (1);
}