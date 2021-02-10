/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_wind_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:19:12 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/10 18:08:32 by tdayde           ###   ########lyon.fr   */
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
			&p->scr.bpp, &p->scr.s_l, &p->scr.endian);
	if (!p->scr.img)
		return (0);
	p->scr.s_l *= 0.25;
	return (1);
}

int	create_text_horiz(t_pars *p)
{
	p->no.img_ptr = mlx_xpm_file_to_image(p->scr.mlx,
			"./pics/greystone.xpm", &p->no.w, &p->no.h);
	if (!p->no.img_ptr)
		return (0);
	p->no.img = (int*)mlx_get_data_addr(p->no.img_ptr,
			&p->no.bpp, &p->no.s_l, &p->no.endian);
	if (!p->no.img)
		return (0);
	p->no.s_l /= 4;
	if (!(p->so.img_ptr = mlx_xpm_file_to_image(\
	p->scr.mlx, "./pics/redbrick.xpm", &p->so.w, &p->so.h)))
		return (0);
	if (!(p->so.img = (int*)mlx_get_data_addr(\
	p->so.img_ptr, &p->so.bpp, &p->so.s_l, &p->so.endian)))
		return (0);
	p->so.s_l /= 4;
	return (1);
}

int	create_text_verti(t_pars *p)
{
	if (!(p->we.img_ptr = mlx_xpm_file_to_image(\
	p->scr.mlx, "./pics/wood.xpm", &p->we.w, &p->we.h)))
		return (0);
	if (!(p->we.img = (int*)mlx_get_data_addr(\
	p->we.img_ptr, &p->we.bpp, &p->we.s_l, &p->we.endian)))
		return (0);
	p->we.s_l /= 4;
	if (!(p->ea.img_ptr = mlx_xpm_file_to_image(\
	p->scr.mlx, "./pics/colorstone.xpm", &p->ea.w, &p->ea.h)))
		return (0);
	if (!(p->ea.img = (int*)mlx_get_data_addr(\
	p->ea.img_ptr, &p->ea.bpp, &p->ea.s_l, &p->ea.endian)))
		return (0);
	p->ea.s_l /= 4;
	return (1);
}

int	create_text_sprite(t_pars *p)
{
	if (!(p->wall.img_ptr = mlx_xpm_file_to_image(\
	p->scr.mlx, "./pics/mur_briques.xpm", &p->wall.w, &p->wall.h)))
		return (0);
	if (!(p->wall.img = (int*)mlx_get_data_addr(\
	p->wall.img_ptr, &p->wall.bpp, &p->wall.s_l, &p->wall.endian)))
		return (0);
	p->wall.s_l /= 4;
	if (!(p->sprite.img_ptr = mlx_xpm_file_to_image(\
	p->scr.mlx, "./pics/pillar.xpm", &p->sprite.w, &p->sprite.h)))
		return (0);
	if (!(p->sprite.img = (int*)mlx_get_data_addr(\
	p->sprite.img_ptr, &p->sprite.bpp, &p->sprite.s_l, &p->sprite.endian)))
		return (0);
	p->sprite.s_l /= 4;
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
