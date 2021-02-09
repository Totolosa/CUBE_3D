/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:47:58 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/09 15:09:26 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_t_ray(t_ray *ray)
{
	// t_contact wall;
	// t_contact **sprites;
	
	// wall = NULL;
	// sprites = NULL;
	ray->wall.x = -1;
	ray->wall.y = -1;
	ray->wall.distance = INT_MAX;
	ray->wall.orient = 0;
	// ray->sprites = NULL;
	// ray->nb_sprites = 0;
	
	// ray->wall = wall;
	// ray->sprites = sprites;
	// ray->nb_sprites = 0;
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
	pars->scr.size_l = 0;
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
	pars->wall.size_l = 0;
	pars->wall.w = 0;
	pars->wall.h = 0;
	pars->wall.endian = 0;
	pars->wall.bpp = 0;

	pars->sprite.path = 0;
	pars->sprite.img_ptr = 0;
	pars->sprite.img = 0;
	pars->sprite.size_l = 0;
	pars->sprite.w = 0;
	pars->sprite.h = 0;
	pars->sprite.endian = 0;
	pars->sprite.bpp = 0;

	pars->text_n.path = 0;
	pars->text_n.img_ptr = 0;
	pars->text_n.img = 0;
	pars->text_n.size_l = 0;
	pars->text_n.w = 0;
	pars->text_n.h = 0;
	pars->text_n.endian = 0;
	pars->text_n.bpp = 0;

	pars->text_s.path = 0;
	pars->text_s.img_ptr = 0;
	pars->text_s.img = 0;
	pars->text_s.size_l = 0;
	pars->text_s.w = 0;
	pars->text_s.h = 0;
	pars->text_s.endian = 0;
	pars->text_s.bpp = 0;

	pars->text_w.path = 0;
	pars->text_w.img_ptr = 0;
	pars->text_w.img = 0;
	pars->text_w.size_l = 0;
	pars->text_w.w = 0;
	pars->text_w.h = 0;
	pars->text_w.endian = 0;
	pars->text_w.bpp = 0;

	pars->text_e.path = 0;
	pars->text_e.img_ptr = 0;
	pars->text_e.img = 0;
	pars->text_e.size_l = 0;
	pars->text_e.w = 0;
	pars->text_e.h = 0;
	pars->text_e.endian = 0;
	pars->text_e.bpp = 0;
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
