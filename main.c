/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:46:18 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/18 17:05:55 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_pars	pars;

	(void)argc;
	setbuf(stdout, NULL);
	init_pars(&pars);
	if (!parsing(&pars, argv[1]))
		quit_prog(&pars);
	modify_img(&pars);
	mlx_hook(pars.scr.win, 02, 1L<<0, update_img, &pars);
	mlx_hook(pars.scr.win, 17, 1L<<0, close_window, &pars);
//	mlx_mouse_hook (pars.win, show_key_code, &pars);
	//mlx_pixel_put(pars->scr.mlx, win, 10, 10, (255*255*255));
	mlx_loop(pars.scr.mlx);
	return (0);
}

//  A FAIRE 
// - Probleme si map sepere par une ligne vide --> OK
// - free line avec GNL --> OK
// - Finir parsing map --> OK
// - Pouvoir fermer le programme si on ferme a la main le fenetre --> OK
// - Mettre au propre .h --> OK
// - Norminette .h
// - Voir quel element bug lorsque pqs de regles debut fichier 
// - Pouvoir sauver la premiere image si deuxieme argument est "--save"

// - Bonus ?
// - colision mur / sprites 
