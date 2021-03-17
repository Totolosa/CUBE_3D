/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:47:58 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/16 17:24:29 by tdayde           ###   ########lyon.fr   */
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

static int	init_one_text(t_text *text)
{
	text->path = 0;
	text->img_ptr = 0;
	text->img = 0;
	text->s_l = 0;
	text->w = 0;
	text->h = 0;
	text->endian = 0;
	text->bpp = 0;
	text->cont = 0;
	return (1);
}

int	init_text(t_pars *pars)
{
	init_one_text(&pars->sky_text);
	init_one_text(&pars->spr_text);
	init_one_text(&pars->no);
	init_one_text(&pars->so);
	init_one_text(&pars->we);
	init_one_text(&pars->ea);
	return (1);
}
