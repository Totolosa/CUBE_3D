/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:58:53 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/10 15:53:00 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_pars *pars)
{
	if (key == KEY_ESC)
		pars->key.close = 1;
	if (key == KEY_LEFT)
		pars->key.turn_left = 1;
	if (key == KEY_RIGHT)
		pars->key.turn_right = 1;
	if (key == KEY_W)
		pars->key.go_front = 1;
	if (key == KEY_S)
		pars->key.go_back = 1;
	if (key == KEY_A)
		pars->key.go_left = 1;
	if (key == KEY_D)
		pars->key.go_right = 1;
	return (1);
}

int	key_release(int key, t_pars *pars)
{
	if (key == KEY_ESC)
		pars->key.close = 0;
	if (key == KEY_LEFT)
		pars->key.turn_left = 0;
	if (key == KEY_RIGHT)
		pars->key.turn_right = 0;
	if (key == KEY_W)
		pars->key.go_front = 0;
	if (key == KEY_S)
		pars->key.go_back = 0;
	if (key == KEY_A)
		pars->key.go_left = 0;
	if (key == KEY_D)
		pars->key.go_right = 0;
	return (1);
}

int	destroy_mlx_all_mallocs(t_pars *pars)
{
	mlx_destroy_image(pars->scr.mlx, pars->scr.img_ptr);
	mlx_destroy_image(pars->scr.mlx, pars->no.img_ptr);
	mlx_destroy_image(pars->scr.mlx, pars->so.img_ptr);
	mlx_destroy_image(pars->scr.mlx, pars->we.img_ptr);
	mlx_destroy_image(pars->scr.mlx, pars->ea.img_ptr);
	mlx_destroy_image(pars->scr.mlx, pars->spr_text.img_ptr);
	mlx_destroy_image(pars->scr.mlx, pars->sky_text.img_ptr);
	mlx_destroy_window(pars->scr.mlx, pars->scr.win);
	return (1);
}

int	close_window(t_pars *pars)
{
	destroy_mlx_all_mallocs(pars);
	ft_lstclear(&pars->free, free);
	write(1, "\nAdios Amigo!\n", 14);
	exit (0);
	return (1);
}

int	update_img(t_pars *p)
{	
	if (p->key.close == 1)
		close_window(p);
	if (p->key.turn_left == 1)
	{
		p->moov.ang -= 4;
		p->moov.x_dir = cos(p->moov.ang / (180 / M_PI));
		p->moov.y_dir = sin(p->moov.ang / (180 / M_PI));
	}
	if (p->key.turn_right == 1)
	{
		p->moov.ang += 4;
		p->moov.x_dir = cos(p->moov.ang / (180 / M_PI));
		p->moov.y_dir = sin(p->moov.ang / (180 / M_PI));
	}
	update_position(p);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, p->scr.win);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, p->scr.img_ptr);
	modify_img(p);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, p->scr.win);
	return (0);
}
