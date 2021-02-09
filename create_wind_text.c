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

int	create_wind(t_pars *p)
{
	p->scr.mlx = mlx_init();
	if (!p->scr.mlx)
		return (0);
	p->scr.win = mlx_new_window(p->scr.mlx, p->scr.w, p->scr.h, "CUB3D");
	if (!p->scr.win)
		return (0);
	p->scr.img_ptr = mlx_new_image(p->scr.mlx, p->scr.w, p->scr.h);
	if (!p->scr.img_ptr)
		return (0);
	p->scr.img = (int*)mlx_get_data_addr(p->scr.img_ptr,
			&p->scr.bpp, &p->scr.size_l, &p->scr.endian);
	if (!p->scr.img)
		return (0);
	p->scr.size_l *= 0.25;
	return (1);
}

int	create_text_horiz(t_pars *p)
{
	p->text_n.img_ptr = mlx_xpm_file_to_image(p->scr.mlx,
			"./pics/greystone.xpm", &p->text_n.w, &p->text_n.h);
	if (!p->text_n.img_ptr)
		return (0);
	p->text_n.img = (int*)mlx_get_data_addr(p->text_n.img_ptr,
			&p->text_n.bpp, &p->text_n.size_l, &p->text_n.endian);
	if (!p->text_n.img)
		return (0);
	p->text_n.size_l /= 4;
	if (!(p->text_s.img_ptr = mlx_xpm_file_to_image(\
	p->scr.mlx, "./pics/redbrick.xpm", &p->text_s.w, &p->text_s.h)))
		return (0);
	if (!(p->text_s.img = (int*)mlx_get_data_addr(\
	p->text_s.img_ptr, &p->text_s.bpp, &p->text_s.size_l, &p->text_s.endian)))
		return (0);
	p->text_s.size_l /= 4;
	return (1);
}

int	create_text_verti(t_pars *p)
{
	if (!(p->text_w.img_ptr = mlx_xpm_file_to_image(\
	p->scr.mlx, "./pics/wood.xpm", &p->text_w.w, &p->text_w.h)))
		return (0);
	if (!(p->text_w.img = (int*)mlx_get_data_addr(\
	p->text_w.img_ptr, &p->text_w.bpp, &p->text_w.size_l, &p->text_w.endian)))
		return (0);
	p->text_w.size_l /= 4;
	if (!(p->text_e.img_ptr = mlx_xpm_file_to_image(\
	p->scr.mlx, "./pics/colorstone.xpm", &p->text_e.w, &p->text_e.h)))
		return (0);
	if (!(p->text_e.img = (int*)mlx_get_data_addr(\
	p->text_e.img_ptr, &p->text_e.bpp, &p->text_e.size_l, &p->text_e.endian)))
		return (0);
	p->text_e.size_l /= 4;
	return (1);
}

int	create_text_sprite(t_pars *p)
{
	if (!(p->wall.img_ptr = mlx_xpm_file_to_image(\
	p->scr.mlx, "./pics/mur_briques.xpm", &p->wall.w, &p->wall.h)))
		return (0);
	if (!(p->wall.img = (int*)mlx_get_data_addr(\
	p->wall.img_ptr, &p->wall.bpp, &p->wall.size_l, &p->wall.endian)))
		return (0);
	p->wall.size_l /= 4;
	if (!(p->sprite.img_ptr = mlx_xpm_file_to_image(\
	p->scr.mlx, "./pics/pillar.xpm", &p->sprite.w, &p->sprite.h)))
		return (0);
	if (!(p->sprite.img = (int*)mlx_get_data_addr(\
	p->sprite.img_ptr, &p->sprite.bpp, &p->sprite.size_l, &p->sprite.endian)))
		return (0);
	p->sprite.size_l /= 4;
	return (1);
}

int	create_all(t_pars *pars)
{
	if (!(create_wind(pars)))
		return (0);
	if (!(create_text_horiz(pars)))
		return (0);
	if (!(create_text_verti(pars)))
		return (0);
	if (!(create_text_sprite(pars)))
		return (0);
	return (1);
}
