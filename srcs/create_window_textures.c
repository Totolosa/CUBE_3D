/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window_textures.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:19:12 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/03 12:30:04 by tdayde           ###   ########lyon.fr   */
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

int	create_text(t_text *text, void *mlx)
{
	text->img_ptr = mlx_xpm_file_to_image(mlx,
			text->path, &text->w, &text->h);
	if (!text->img_ptr)
		return (0);
	text->img = (int*)mlx_get_data_addr(text->img_ptr,
			&text->bpp, &text->s_l, &text->endian);
	if (!text->img)
		return (0);
	text->s_l /= 4;
	text->cont = text->img[0];
	return (1);
}

int	create_window_textures(t_pars *pars)
{
	if (pars->scr.w == 0 || pars->scr.h == 0)
		quit_prog("Window size issue\n", pars);
	if (!(create_wind(pars)))
		quit_prog("Window creation failed\n", pars);
	if (!(create_text(&pars->no, pars->scr.mlx)))
		quit_prog("North texture creation failed\n", pars);
	if (!(create_text(&pars->so, pars->scr.mlx)))
		quit_prog("South texture creation failed\n", pars);
	if (!(create_text(&pars->we, pars->scr.mlx)))
		quit_prog("West texture creation failed\n", pars);
	if (!(create_text(&pars->ea, pars->scr.mlx)))
		quit_prog("East texture creation failed\n", pars);
	if (!(create_text(&pars->spr_text, pars->scr.mlx)))
		quit_prog("Sprite texture creation failed\n", pars);
	if (!(create_text(&pars->sky_text, pars->scr.mlx)))
		quit_prog("Sky texture creation failed\n", pars);
	return (1);
}
