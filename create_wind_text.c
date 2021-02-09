/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_wind_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:19:12 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/09 15:45:12 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int create_wind(t_pars *p)
{
	if (!(p->scr.mlx = mlx_init()))
		return (0);
	if (!(p->scr.win = mlx_new_window \
	(p->scr.mlx, p->scr.w, p->scr.h, "CUB3D")))
		return (0);
	if (!(p->scr.img_ptr = mlx_new_image(p->scr.mlx, p->scr.w, p->scr.h)))
		return (0);
	if (!(p->scr.img = (int*)mlx_get_data_addr \
	(p->scr.img_ptr, &p->scr.bpp, &p->scr.size_l, &p->scr.endian)))
		return (0);
	p->scr.size_l /= 4;
	return (1);
}

int create_text_horiz(t_pars *p)
{
	if (!(p->text_n.img_ptr = mlx_xpm_file_to_image \
	(p->scr.mlx, "./pics/greystone.xpm", &p->text_n.w, &p->text_n.h)))
		return (0);
	if (!(p->text_n.img = (int*)mlx_get_data_addr \
	(p->text_n.img_ptr, &p->text_n.bpp, &p->text_n.size_l, &p->text_n.endian)))
		return (0);
	p->text_n.size_l /= 4;
	if (!(p->text_s.img_ptr = mlx_xpm_file_to_image \
	(p->scr.mlx, "./pics/redbrick.xpm", &p->text_s.w, &p->text_s.h)))
		return (0);
	if (!(p->text_s.img = (int*)mlx_get_data_addr \
	(p->text_s.img_ptr, &p->text_s.bpp, &p->text_s.size_l, &p->text_s.endian)))
		return (0);
	p->text_s.size_l /= 4;
	return (1);
}

int create_text_verti(t_pars *p)
{
	if (!(p->text_w.img_ptr = mlx_xpm_file_to_image \
	(p->scr.mlx, "./pics/wood.xpm", &p->text_w.w, &p->text_w.h)))
		return (0);
	if (!(p->text_w.img = (int*)mlx_get_data_addr \
	(p->text_w.img_ptr, &p->text_w.bpp, &p->text_w.size_l, &p->text_w.endian)))
		return (0);
	p->text_w.size_l /= 4;
	if (!(p->text_e.img_ptr = mlx_xpm_file_to_image \
	(p->scr.mlx, "./pics/colorstone.xpm", &p->text_e.w, &p->text_e.h)))
		return (0);
	if (!(p->text_e.img = (int*)mlx_get_data_addr \
	(p->text_e.img_ptr, &p->text_e.bpp, &p->text_e.size_l, &p->text_e.endian)))
		return (0);
	p->text_e.size_l /= 4;
	return (1);
}

int	create_all(t_pars *pars)
{
	if (!(create_wind(pars)))
		return (0);
	// create_text_horiz(pars);
	// create_text_verti(pars);
	pars->text_n.img_ptr = mlx_xpm_file_to_image(pars->scr.mlx, "./pics/greystone.xpm", &pars->text_n.w, &pars->text_n.h);
	pars->text_n.img = (int*)mlx_get_data_addr(pars->text_n.img_ptr, &pars->text_n.bpp, &pars->text_n.size_l, &pars->text_n.endian);
	pars->text_n.size_l /= 4;
	pars->text_s.img_ptr = mlx_xpm_file_to_image(pars->scr.mlx, "./pics/redbrick.xpm", &pars->text_s.w, &pars->text_s.h);
	pars->text_s.img = (int*)mlx_get_data_addr(pars->text_s.img_ptr, &pars->text_s.bpp, &pars->text_s.size_l, &pars->text_s.endian);
	pars->text_s.size_l /= 4;
	pars->text_w.img_ptr = mlx_xpm_file_to_image(pars->scr.mlx, "./pics/wood.xpm", &pars->text_w.w, &pars->text_w.h);
	pars->text_w.img = (int*)mlx_get_data_addr(pars->text_w.img_ptr, &pars->text_w.bpp, &pars->text_w.size_l, &pars->text_w.endian);
	pars->text_w.size_l /= 4;
	pars->text_e.img_ptr = mlx_xpm_file_to_image(pars->scr.mlx, "./pics/colorstone.xpm", &pars->text_e.w, &pars->text_e.h);
	pars->text_e.img = (int*)mlx_get_data_addr(pars->text_e.img_ptr, &pars->text_e.bpp, &pars->text_e.size_l, &pars->text_e.endian);
	pars->text_e.size_l /= 4;
	pars->wall.img_ptr = mlx_xpm_file_to_image(pars->scr.mlx, "./pics/mur_briques.xpm", &pars->wall.w, &pars->wall.h);
	pars->wall.img = (int*)mlx_get_data_addr(pars->wall.img_ptr, &pars->wall.bpp, &pars->wall.size_l, &pars->wall.endian);
	pars->wall.size_l /= 4;
	pars->sprite.img_ptr = mlx_xpm_file_to_image(pars->scr.mlx, "./pics/pillar.xpm", &pars->sprite.w, &pars->sprite.h);
	pars->sprite.img = (int*)mlx_get_data_addr(pars->sprite.img_ptr, &pars->sprite.bpp, &pars->sprite.size_l, &pars->sprite.endian);
	pars->sprite.size_l /= 4;
	return (1);
}