/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:46:18 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/16 17:37:44 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_pars	pars;

	setbuf(stdout, NULL);
	init_pars(&pars);
	if (argc != 2 && argc != 3)
		quit_prog("Number of argument(s) error\n", &pars);
	if (!parsing(&pars, argv[1]))
		quit_prog("Parsing failed\n", &pars);
	modify_img(&pars);
	if (argc == 3)
	{
		if (!ft_strncmp(argv[2], "--save", len_save(argv[2])))
		{
			save_bmp("save.bmp", &pars);
			exit (0);
		}
		quit_prog("Save argument error\n", &pars);
	}
	mlx_hook(pars.scr.win, 02, 1L << 0, key_press, &pars);
	mlx_hook(pars.scr.win, 03, 1L << 1, key_release, &pars);
	mlx_hook(pars.scr.win, 17, 1L << 0, close_window, &pars);
	mlx_loop_hook(pars.scr.mlx, update_img, &pars);
	mlx_loop(pars.scr.mlx);
	return (0);
}
