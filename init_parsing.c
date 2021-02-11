/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 08:10:55 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/11 12:13:32 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_moov(t_pars *pars)
{
	pars->moov.x_pos = 0;
	pars->moov.y_pos = 0;
	pars->moov.ang = 0;
	pars->moov.x_dir = 0;
	pars->moov.y_dir = 0;
	pars->moov.ang_pix = 0;
	pars->moov.speed = 0;
}

void	init_screen(t_pars *pars)
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

void	init_map(t_pars *pars)
{
	pars->map.map_file = 0;
	pars->map.map = 0;
	pars->map.map_w = 0;
	pars->map.map_h = 0;
}

int	init_pars(t_pars *pars)
{
	pars->free = ft_alloc(sizeof(t_list), pars);
	pars->free->content = 0;
	pars->free->next = 0;
	init_moov(pars);
	init_screen(pars);
	init_map(pars);
	pars->spr = 0;
	pars->nb_spr = 0;
	pars->sky_col = 0;
	pars->floor_col = 0;
	pars->wall_h = 0;
	pars->player_h = 0;
	return (1);
}
