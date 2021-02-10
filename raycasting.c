/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:38:20 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/10 16:55:38 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int init_first_wall_horiz(double *x, int *y, t_ray *horiz, t_pars *pars)
{
	if (horiz->y_dir > 0)
		horiz->wall.orient = 's';
	else 
		horiz->wall.orient = 'n';
	
	if (horiz->y_dir > 0 && pars->moov.y_pos != floor(pars->moov.y_pos))
		*y = (int)pars->moov.y_pos + 1;
	else 
		*y = (int)pars->moov.y_pos;
	if (fabs(horiz->y_dir) != 1)
		*x = pars->moov.x_pos + (((double)*y - pars->moov.y_pos)
        / (horiz->y_dir / horiz->x_dir));
	else 
		*x = pars->moov.x_pos;
    return (1);
}

int first_wall_horiz(t_ray *horiz, t_pars *pars)
{
	double x;
	int y;

    init_first_wall_horiz(&x, &y, horiz, pars);
	while (continue_ray_horiz(x, y, horiz, pars))
	{
		if ((horiz->y_dir > 0 && pars->map.map[y][(int)x] == 1)
        || (horiz->y_dir < 0 && pars->map.map[y - 1][(int)x] == 1))
		{
			horiz->wall.x = x;
			horiz->wall.y = y;
			horiz->wall.dst = sqrt(pow(horiz->wall.y - pars->moov.y_pos, 2)
            + pow(horiz->wall.x - pars->moov.x_pos, 2));
			return (1);
		}
		if (horiz->y_dir > 0)
			y += 1;
		else 
			y -= 1;
		if (fabs(horiz->y_dir) != 1)
			x = pars->moov.x_pos + (((double)y - pars->moov.y_pos)
            / (horiz->y_dir / horiz->x_dir));
	}
	return (1);
}

int init_first_wall_verti(int *x, double *y, t_ray *verti, t_pars *pars)
{
    if (verti->x_dir > 0)
		verti->wall.orient = 'e';
	else 
		verti->wall.orient = 'w';
	
	if (verti->x_dir > 0 && pars->moov.x_pos != floor(pars->moov.x_pos))
		*x = (int)pars->moov.x_pos + 1;
	else 
		*x = (int)pars->moov.x_pos;
	if (fabs(verti->x_dir) != 1)
		*y = pars->moov.y_pos + (((double)*x - pars->moov.x_pos)
        * (verti->y_dir / verti->x_dir));
	else 
		*y = pars->moov.y_pos;
    return (1);
}

int first_wall_verti(t_ray *verti, t_pars *pars)
{
	int x;
	double y;

    init_first_wall_verti(&x, &y, verti, pars);
	while (continue_ray_verti(x, y, verti, pars))
	{
		if ((verti->x_dir > 0 && pars->map.map[(int)y][x] == 1)
        || (verti->x_dir < 0 && pars->map.map[(int)y][x - 1] == 1))
		{
			verti->wall.x = x;
			verti->wall.y = y;
			verti->wall.dst = sqrt(pow(verti->wall.y - pars->moov.y_pos, 2)
            + pow(verti->wall.x - pars->moov.x_pos, 2));
			return (1);
		}
		if (verti->x_dir > 0)
			x += 1;
		else 
			x -= 1;
		if (fabs(verti->x_dir) != 1)
			y = pars->moov.y_pos + (((double)x - pars->moov.x_pos)
            * (verti->y_dir / verti->x_dir));
	}
	return (1);
}

int find_wall_contact(t_ray *ray, t_pars *pars)
{
	t_ray horiz;
	t_ray verti;

	init_t_ray(ray->angle, &horiz);
	init_t_ray(ray->angle, &verti);
	if (fabs(ray->x_dir) != 1)
		first_wall_horiz(&horiz, pars);
	if (fabs(ray->y_dir) != 1)
		first_wall_verti(&verti, pars);
	horiz_or_verti(ray, horiz, verti);
	ray->wall.dst = cos(fabs((pars->moov.ang / (180 / M_PI)) - ray->angle))
	* ray->wall.dst;
	return (1);
}