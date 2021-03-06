/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 08:10:55 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/11 17:37:43 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_keys(t_pars *pars)
{
	pars->key.go_front = 0;
	pars->key.go_back = 0;
	pars->key.go_left = 0;
	pars->key.go_right = 0;
	pars->key.turn_left = 0;
	pars->key.turn_right = 0;
	pars->key.close = 0;
}

void	init_moov(t_pars *pars)
{
	pars->moov.x_pos = 0;
	pars->moov.y_pos = 0;
	pars->moov.ang = 0;
	pars->moov.x_dir = 0;
	pars->moov.y_dir = 0;
	pars->moov.ang_pix = 0;
	pars->moov.spd = 0.11;
}

void	init_screen(t_pars *pars)
{
	pars->scr.mlx = 0;
	pars->scr.win = 0;
	pars->scr.w = 0;
	pars->scr.h = 0;
	pars->scr.real_w = 0;
	pars->scr.real_h = 0;
	pars->scr.d = 0;
	pars->scr.fov = 60;
	pars->scr.img_ptr = 0;
	pars->scr.img = 0;
	pars->scr.s_l = 0;
}

void	init_map(t_pars *pars)
{
	pars->map.map_file = 0;
	pars->map.map = 0;
	pars->map.map_w = 0;
	pars->map.map_h = 0;
}

int	init_pars(t_pars *pars)
{
	init_keys(pars);
	init_moov(pars);
	init_screen(pars);
	init_map(pars);
	pars->free = NULL;
	pars->spr = 0;
	pars->nb_spr = 0;
	pars->w_dst_col = 0;
	pars->sky_col = 0;
	pars->floor_col = 0;
	pars->wall_h = 64;
	pars->player_h = pars->wall_h / 2;
	return (1);
}
