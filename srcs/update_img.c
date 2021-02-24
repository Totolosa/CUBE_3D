/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:58:53 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/24 13:52:31 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_pars *pars)
{
	if (key == 53)
		pars->key.close = 1;
	if (key == 123)
		pars->key.turn_left = 1;
	if (key == 124)
		pars->key.turn_right = 1;
	if (key == 13)
		pars->key.go_front = 1;
	if (key == 1)
		pars->key.go_back = 1;
	if (key == 0)
		pars->key.go_left = 1;
	if (key == 2)
		pars->key.go_right = 1;
	return (1);
}

int	key_release(int key, t_pars *pars)
{
	if (key == 53)
		pars->key.close = 0;
	if (key == 123)
		pars->key.turn_left = 0;
	if (key == 124)
		pars->key.turn_right = 0;
	if (key == 13)
		pars->key.go_front = 0;
	if (key == 1)
		pars->key.go_back = 0;
	if (key == 0)
		pars->key.go_left = 0;
	if (key == 2)
		pars->key.go_right = 0;
	return (1);
}

int	close_window(t_pars *pars)
{
	mlx_destroy_window(pars->scr.mlx, pars->scr.win);
	ft_lstclear(&pars->free, free);
	write(1, "\nAdios Amigo!\n", 14);
	exit (0);
	return (1);
}

int	update_position(t_pars *p)
{
	if (p->key.go_front == 1)
	{
		p->moov.x_pos += p->moov.x_dir * p->moov.spd;
		p->moov.y_pos += p->moov.y_dir * p->moov.spd;
	}
	if (p->key.go_back == 1)
	{
		p->moov.x_pos -= p->moov.x_dir * p->moov.spd;
		p->moov.y_pos -= p->moov.y_dir * p->moov.spd;
	}
	if (p->key.go_left == 1)
	{
		p->moov.x_pos += (cos((p->moov.ang - 90) / (180 / M_PI)) * p->moov.spd);
		p->moov.y_pos += (sin((p->moov.ang - 90) / (180 / M_PI)) * p->moov.spd);
	}
	if (p->key.go_right == 1)
	{
		p->moov.x_pos += (cos((p->moov.ang + 90) / (180 / M_PI)) * p->moov.spd);
		p->moov.y_pos += (sin((p->moov.ang + 90) / (180 / M_PI)) * p->moov.spd);
	}
	return (0);
}

int	update_img(t_pars *p)
{	
	if (p->key.close == 1)
		close_window(p);
	if (p->key.turn_left == 1)
	{
		p->moov.ang -= 3;
		p->moov.x_dir = cos(p->moov.ang / (180 / M_PI));
		p->moov.y_dir = sin(p->moov.ang / (180 / M_PI));
	}
	if (p->key.turn_right == 1)
	{
		p->moov.ang += 3;
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
