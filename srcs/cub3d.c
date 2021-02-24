/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:32:35 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/23 16:45:20 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(t_pars *pars, char *file)
{
	parsing_first_part(file, pars);
	create_window_textures(pars);
	create_map(pars, -1);
	fill_map(pars);
	check_map(pars);
	return (1);
}

int	modify_img(t_pars *p)
{
	t_ray	ray;
	int		i;

	i = 0;
	init_t_ray((p->moov.ang - (p->scr.fov / 2)) / (180 / M_PI), &ray);
	while (i < p->scr.w)
	{
		find_wall_contact(&ray, p);
		p->w_dst_col[i] = ray.wall.dst;
		print_wall_col(&ray, i, p);
		i++;
		init_t_ray((p->moov.ang - (p->scr.fov / 2)
		+ p->moov.ang_pix * (i + 1)) / (180 / M_PI), &ray);
	}
	if (p->nb_spr > 0)
	{
		calcul_h_sprite(p);
		print_sprites(p);
	}
	mlx_put_image_to_window(p->scr.mlx, p->scr.win, p->scr.img_ptr, 0, 0);
	return (1);
}
