/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:32:35 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/16 16:38:40 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	modify_img(t_pars *pars)
{
	t_ray	ray;
	int		i;

	i = 0;
	init_t_ray((pars->moov.ang - (pars->scr.fov / 2)) / (180 / M_PI), &ray);
	while (i < pars->scr.w)
	{
		find_wall_contact(&ray, pars);
		pars->w_dst_col[i] = ray.wall.dst;
		print_wall_col(&ray, i, pars);
		i++;
		init_t_ray((pars->moov.ang - (pars->scr.fov / 2)
		+ pars->moov.ang_pix * (i + 1)) / (180 / M_PI), &ray);
	}
	if (pars->nb_spr > 0)
	{
		calcul_h_sprite(pars);
		print_sprites(pars);
	}
}

int update_img(int key_code, t_pars *pars)
{	
	ft_putnbr_fd(key_code, 1);
	if (key_code == 53)
	{
		mlx_destroy_window(pars->scr.mlx, pars->scr.win );
		ft_lstclear(&pars->free, free);
		write(1, "\nAdios Amigo!\n", 14);
		exit (0);
	}
	if (key_code == 123)
	{
		pars->moov.ang -= 5;
		pars->moov.x_dir = cos(pars->moov.ang / (180 / M_PI));
		pars->moov.y_dir = sin(pars->moov.ang / (180 / M_PI));
		modify_img(pars);
		mlx_put_image_to_window(pars->scr.mlx, pars->scr.win, pars->scr.img_ptr, 0, 0);
	}
	if (key_code == 124)
	{
		pars->moov.ang += 5;
		pars->moov.x_dir = cos(pars->moov.ang / (180 / M_PI));
		pars->moov.y_dir = sin(pars->moov.ang / (180 / M_PI));
		modify_img(pars);
		mlx_put_image_to_window(pars->scr.mlx, pars->scr.win, pars->scr.img_ptr, 0, 0);
	}
	if (key_code == 13)
	{
		pars->moov.x_pos+= pars->moov.x_dir * pars->moov.speed;
		pars->moov.y_pos+= pars->moov.y_dir * pars->moov.speed;
		modify_img(pars);
		mlx_put_image_to_window(pars->scr.mlx, pars->scr.win, pars->scr.img_ptr, 0, 0);
	}
	if (key_code == 1)
	{
		pars->moov.x_pos-= pars->moov.x_dir * pars->moov.speed;
		pars->moov.y_pos-= pars->moov.y_dir * pars->moov.speed;
		modify_img(pars);
		mlx_put_image_to_window(pars->scr.mlx, pars->scr.win, pars->scr.img_ptr, 0, 0);
	}
	if (key_code == 0)
	{
		pars->moov.x_pos+= (cos((pars->moov.ang- 90) / (180 / M_PI)) * pars->moov.speed);
		pars->moov.y_pos+= (sin((pars->moov.ang- 90) / (180 / M_PI)) * pars->moov.speed);
		modify_img(pars);
		mlx_put_image_to_window(pars->scr.mlx, pars->scr.win, pars->scr.img_ptr, 0, 0);
	}
	if (key_code == 2)
	{
		pars->moov.x_pos+= (cos((pars->moov.ang+ 90) / (180 / M_PI)) * pars->moov.speed);
		pars->moov.y_pos+= (sin((pars->moov.ang+ 90) / (180 / M_PI)) * pars->moov.speed);
		modify_img(pars);
		mlx_put_image_to_window(pars->scr.mlx, pars->scr.win, pars->scr.img_ptr, 0, 0);
	}
	if (key_code == 17)
	{
		mlx_put_image_to_window(pars->scr.mlx, pars->scr.win, pars->spr_text.img_ptr, 0, 0);
	}
	return (0);
}
