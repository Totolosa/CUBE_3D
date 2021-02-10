/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:47:58 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/10 18:08:32 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_t_ray(double angle, t_ray *ray)
{
	ray->wall.x = -1;
	ray->wall.y = -1;
	ray->wall.dst = INT_MAX;
	ray->wall.orient = 0;
	ray->angle = angle;
	ray->x_dir = cos(angle);
	ray->y_dir = sin(angle);
	ray->w_scr_h = 0;
	ray->sky_h = 0;
	ray->line = 0;
}

void init_moov(t_pars *pars)
{
	pars->moov.x_pos = 0;
	pars->moov.y_pos = 0;
	pars->moov.ang = 0;
	pars->moov.x_dir = 0;
	pars->moov.y_dir = 0;
	pars->moov.ang_pix = 0;
	pars->moov.speed = 0;
}

void init_screen(t_pars *pars)
{
	pars->scr.mlx = 0;
	pars->scr.win = 0;
	pars->scr.w = 0;
	pars->scr.h = 0;
	pars->scr.d = 0;
	pars->scr.fov = 0;
	pars->scr.img_ptr = 0;
	pars->scr.img = 0;
	pars->scr.s_l = 0;
}

void init_map(t_pars *pars)
{
	pars->map.map_file = 0;
	pars->map.map = 0;
	pars->map.map_w = 0;
	pars->map.map_h = 0;
}

void init_text(t_pars *pars)
{
	pars->wall.path = 0;
	pars->wall.img_ptr = 0;
	pars->wall.img = 0;
	pars->wall.s_l = 0;
	pars->wall.w = 0;
	pars->wall.h = 0;
	pars->wall.endian = 0;
	pars->wall.bpp = 0;

	pars->sprite.path = 0;
	pars->sprite.img_ptr = 0;
	pars->sprite.img = 0;
	pars->sprite.s_l = 0;
	pars->sprite.w = 0;
	pars->sprite.h = 0;
	pars->sprite.endian = 0;
	pars->sprite.bpp = 0;

	pars->no.path = 0;
	pars->no.img_ptr = 0;
	pars->no.img = 0;
	pars->no.s_l = 0;
	pars->no.w = 0;
	pars->no.h = 0;
	pars->no.endian = 0;
	pars->no.bpp = 0;

	pars->so.path = 0;
	pars->so.img_ptr = 0;
	pars->so.img = 0;
	pars->so.s_l = 0;
	pars->so.w = 0;
	pars->so.h = 0;
	pars->so.endian = 0;
	pars->so.bpp = 0;

	pars->we.path = 0;
	pars->we.img_ptr = 0;
	pars->we.img = 0;
	pars->we.s_l = 0;
	pars->we.w = 0;
	pars->we.h = 0;
	pars->we.endian = 0;
	pars->we.bpp = 0;

	pars->ea.path = 0;
	pars->ea.img_ptr = 0;
	pars->ea.img = 0;
	pars->ea.s_l = 0;
	pars->ea.w = 0;
	pars->ea.h = 0;
	pars->ea.endian = 0;
	pars->ea.bpp = 0;
}

void init_pars(t_pars *pars)
{
	init_moov(pars);
	init_screen(pars);
	init_map(pars);

	pars->wall_h = 0;
	pars->player_h = 0;

	pars->spr = 0;
	pars->nb_spr = 0;

	pars->sky_col = 0;
	pars->floor_col = 0;
	pars->wall_col = 0;
	
	pars->free = 0;
}
