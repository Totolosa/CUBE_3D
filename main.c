/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:46:18 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/17 18:00:55 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	(void)argc;
	t_pars pars;

	setbuf(stdout, NULL);
	init_pars(&pars);
	if (!parsing(&pars, argv[1]))
		quit_prog(&pars);
//	printf("screen.w = %d, screen.h = %d, screen.d = %f, screen.sl = %d\n", pars.scr.w, pars.scr.h, pars.scr.d, pars.scr.s_l);
	modify_img(&pars);
	mlx_put_image_to_window(pars.scr.mlx, pars.scr.win, pars.scr.img_ptr, 0, 0);
	mlx_hook(pars.scr.win, 02, 1L<<0, update_img, &pars);
//	mlx_mouse_hook (pars.win, show_key_code, &pars);
	//mlx_pixel_put(pars->scr.mlx, win, 10, 10, (255*255*255));
	mlx_loop(pars.scr.mlx);
	return (0);
}

//  A FAIRE 
// - Probleme si map sepere par une ligne vide --> OK
// - free line avec GNL --> OK
// - Finir parsing map
// - Mettre au propre .h
// - Norminette
// - Pouvoir fermer le programme si on ferme a la main le fenetre
// - Pouvoir sauver la premiere image si deuxieme argument est "--save"
// - Bonus ?