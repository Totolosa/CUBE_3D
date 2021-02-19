/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:32:35 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/18 16:57:36 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(t_pars *pars, char *file)
{
	pars->map.map_file = file;
	parsing_first_part(pars);
	create_window_textures(pars);
	create_map(pars, -1);
	fill_map(pars);
	check_map(pars);
	return (1);
}

void	modify_img(t_pars *p)
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
}

int	close_window(t_pars *pars)
{
	mlx_destroy_window(pars->scr.mlx, pars->scr.win);
	ft_lstclear(&pars->free, free);
	write(1, "\nAdios Amigo!\n", 14);
	exit (0);
	return (1);
}

int	update_position(int key_code, t_pars *p)
{
	if (key_code == 13)
	{
		p->moov.x_pos += p->moov.x_dir * p->moov.spd;
		p->moov.y_pos += p->moov.y_dir * p->moov.spd;
		modify_img(p);
	}
	if (key_code == 1)
	{
		p->moov.x_pos -= p->moov.x_dir * p->moov.spd;
		p->moov.y_pos -= p->moov.y_dir * p->moov.spd;
		modify_img(p);
	}
	if (key_code == 0)
	{
		p->moov.x_pos += (cos((p->moov.ang - 90) / (180 / M_PI)) * p->moov.spd);
		p->moov.y_pos += (sin((p->moov.ang - 90) / (180 / M_PI)) * p->moov.spd);
		modify_img(p);
	}
	if (key_code == 2)
	{
		p->moov.x_pos += (cos((p->moov.ang + 90) / (180 / M_PI)) * p->moov.spd);
		p->moov.y_pos += (sin((p->moov.ang + 90) / (180 / M_PI)) * p->moov.spd);
		modify_img(p);
	}
	return (0);
}

int	update_img(int key_code, t_pars *p)
{	
	ft_putnbr_fd(key_code, 1);
	if (key_code == 53)
		close_window(p);
	if (key_code == 123)
	{
		p->moov.ang -= 5;
		p->moov.x_dir = cos(p->moov.ang / (180 / M_PI));
		p->moov.y_dir = sin(p->moov.ang / (180 / M_PI));
		modify_img(p);
	}
	if (key_code == 124)
	{
		p->moov.ang += 5;
		p->moov.x_dir = cos(p->moov.ang / (180 / M_PI));
		p->moov.y_dir = sin(p->moov.ang / (180 / M_PI));
		modify_img(p);
	}
	if (key_code == 13 || key_code == 0 || key_code == 1 || key_code == 2)
		update_position(key_code, p);
	return (0);
}
