/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window_textures.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:19:12 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/19 13:53:04 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_wind(t_pars *p)
{
	p->scr.mlx = mlx_init();
	if (!p->scr.mlx)
		return (0);
	mlx_get_screen_size(p->scr.mlx, &p->scr.real_w, &p->scr.real_h);
	if (p->scr.w > p->scr.real_w)
		p->scr.w = p->scr.real_w;
	if (p->scr.h > p->scr.real_h)
		p->scr.h = p->scr.real_h;
	p->scr.win = mlx_new_window(p->scr.mlx, p->scr.w, p->scr.h, "CUB3D");
	if (!p->scr.win)
		return (0);
	p->scr.img_ptr = mlx_new_image(p->scr.mlx, p->scr.w, p->scr.h);
	if (!p->scr.img_ptr)
		return (0);
	p->scr.img = (int*)mlx_get_data_addr(p->scr.img_ptr,
			&p->scr.bpp, &p->scr.s_l, &p->scr.endian);
	if (!p->scr.img)
		return (0);
	p->scr.s_l /= 4;
	p->w_dst_col = ft_alloc(sizeof(double) * p->scr.w, p->free);
	p->moov.ang_pix = p->scr.fov / (double)p->scr.w;
	p->scr.d = ((double)p->scr.w / 2)
		/ tan((p->scr.fov / 2) / (180 / M_PI));
	return (1);
}

int	create_text_horiz(t_pars *p)
{
	p->no.img_ptr = mlx_xpm_file_to_image(p->scr.mlx,
			p->no.path, &p->no.w, &p->no.h);
	if (!p->no.img_ptr)
		return (0);
	p->no.img = (int*)mlx_get_data_addr(p->no.img_ptr,
			&p->no.bpp, &p->no.s_l, &p->no.endian);
	if (!p->no.img)
		return (0);
	p->no.s_l /= 4;
	p->so.img_ptr = mlx_xpm_file_to_image(p->scr.mlx,
			p->so.path, &p->so.w, &p->so.h);
	if (!p->so.img_ptr)
		return (0);
	p->so.img = (int*)mlx_get_data_addr(p->so.img_ptr,
			&p->so.bpp, &p->so.s_l, &p->so.endian);
	if (!p->so.img)
		return (0);
	p->so.s_l /= 4;
	return (1);
}

int	create_text_verti(t_pars *p)
{
	p->we.img_ptr = mlx_xpm_file_to_image(p->scr.mlx,
			p->we.path, &p->we.w, &p->we.h);
	if (!p->we.img_ptr)
		return (0);
	p->we.img = (int*)mlx_get_data_addr(p->we.img_ptr,
			&p->we.bpp, &p->we.s_l, &p->we.endian);
	if (!p->we.img)
		return (0);
	p->we.s_l /= 4;
	p->ea.img_ptr = mlx_xpm_file_to_image(p->scr.mlx,
			p->ea.path, &p->ea.w, &p->ea.h);
	if (!p->ea.img_ptr)
		return (0);
	p->ea.img = (int*)mlx_get_data_addr(p->ea.img_ptr,
			&p->ea.bpp, &p->ea.s_l, &p->ea.endian);
	if (!p->ea.img)
		return (0);
	p->ea.s_l /= 4;
	return (1);
}

int	create_text_sprite(t_pars *p)
{
	p->spr_text.img_ptr = mlx_xpm_file_to_image(p->scr.mlx,
			p->spr_text.path, &p->spr_text.w, &p->spr_text.h);
	if (!p->spr_text.img_ptr)
		return (0);
	p->spr_text.img = (int*)mlx_get_data_addr(p->spr_text.img_ptr,
			&p->spr_text.bpp, &p->spr_text.s_l, &p->spr_text.endian);
	if (!p->spr_text.img)
		return (0);
	p->spr_text.s_l /= 4;
	p->spr_text.cont = p->spr_text.img[0];
	return (1);
}

int	create_window_textures(t_pars *pars)
{
	if (pars->scr.w == 0 || pars->scr.h == 0)
		quit_prog("Window size issue\n", pars);
	if (!(create_wind(pars)))
		quit_prog("Window creation issue\n", pars);
	if (!(create_text_horiz(pars)))
		quit_prog("Texture creation failed\n", pars);
	if (!(create_text_verti(pars)))
		quit_prog("Texture creation failed\n", pars);
	if (!(create_text_sprite(pars)))
		quit_prog("Sprite texture creation failed\n", pars);
	return (1);
}
