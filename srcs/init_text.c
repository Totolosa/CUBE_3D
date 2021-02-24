/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:47:58 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/19 14:11:04 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_print_text(t_print_text *text)
{
	text->scale_h = 0;
	text->scale_w = 0;
	text->x = 0;
	text->y = 0;
	return (1);
}

int	init_text_horiz(t_pars *pars)
{
	pars->no.path = 0;
	pars->no.img_ptr = 0;
	pars->no.img = 0;
	pars->no.s_l = 0;
	pars->no.w = 0;
	pars->no.h = 0;
	pars->no.endian = 0;
	pars->no.bpp = 0;
	pars->so.path = 0;
	pars->so.img_ptr = 0;
	pars->so.img = 0;
	pars->so.s_l = 0;
	pars->so.w = 0;
	pars->so.h = 0;
	pars->so.endian = 0;
	pars->so.bpp = 0;
	return (1);
}

int	init_text_verti(t_pars *pars)
{
	pars->we.path = 0;
	pars->we.img_ptr = 0;
	pars->we.img = 0;
	pars->we.s_l = 0;
	pars->we.w = 0;
	pars->we.h = 0;
	pars->we.endian = 0;
	pars->we.bpp = 0;
	pars->ea.path = 0;
	pars->ea.img_ptr = 0;
	pars->ea.img = 0;
	pars->ea.s_l = 0;
	pars->ea.w = 0;
	pars->ea.h = 0;
	pars->ea.endian = 0;
	pars->ea.bpp = 0;
	return (1);
}

int	init_text(t_pars *pars)
{
	init_text_horiz(pars);
	init_text_verti(pars);
	pars->spr_text.path = 0;
	pars->spr_text.img_ptr = 0;
	pars->spr_text.img = 0;
	pars->spr_text.s_l = 0;
	pars->spr_text.w = 0;
	pars->spr_text.h = 0;
	pars->spr_text.endian = 0;
	pars->spr_text.bpp = 0;
	return (1);
}
