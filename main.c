/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:46:18 by tdayde            #+#    #+#             */
/*   Updated: 2021/01/12 19:57:07 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int show_key_code(int key_code, t_info *parsing)
{	
	(void)parsing;
	ft_putnbr_fd(key_code, 1);
	if (key_code == 53)
	{
		mlx_destroy_window(parsing->mlx_ptr, parsing->win_ptr );
		exit(0);
	//	return (1);
	}
	return (0);
}

int modify_img(char *img, t_info *parsing)
{
	(void)img;
	(void)parsing;
	return (0);
}

int parsing_map(t_info *parsing, char *file)
{
	(void)file;
	parsing->fov = 60;
	parsing->width_screen = 1000;
	parsing->height_screen = 700;
	parsing->angle_per_pix = (double)parsing->fov / (double)parsing->width_screen;
	parsing->distance_screen = (double)parsing->width_screen / tan((float)(parsing->fov / 2)*180/3.1415927);
	printf("angle/pixel = %f, tan(30) = %f, distance screen = %d\n", parsing->angle_per_pix, tan((float)(parsing->fov / 2)*180/3.1415927), parsing->distance_screen);
	return (0);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_info parsing = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	int i, j = 9;
	int bpp;
	int size_line;
	int endian;
	//int width, height;
	// void *mlx_ptr;
	// void *win_ptr;
	void *img_ptr;
	char *img; 
	// void *img_wall_ptr;
	// char *img_wall;

	if ((parsing_map(&parsing, argv[1]) == -1))
		exit (0);
	parsing.mlx_ptr = mlx_init();
	parsing.win_ptr = mlx_new_window(parsing.mlx_ptr, parsing.width_screen, parsing.height_screen, "CUB3D");
	img_ptr = mlx_new_image(parsing.mlx_ptr, 100, 100);
	img = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	// img_wall_ptr = mlx_xpm_file_to_image(parsing.mlx_ptr, "img_stone_wall.xpm", &width, &height);
	// img_wall = mlx_get_data_addr(img_wall_ptr, &bpp, &size_line, &endian);
	modify_img(img, &parsing);
	while (++j <= 50)
	{
		i = 9;
		while (++i <= 50)
			((int*)img)[(i) + (j * size_line / 4)] = 0x00ffffff;
	}
	mlx_put_image_to_window(parsing.mlx_ptr, parsing.win_ptr, img_ptr, 50, 50);
	mlx_key_hook(parsing.win_ptr, show_key_code, &parsing);
	mlx_mouse_hook (parsing.win_ptr, show_key_code, &parsing);
	//mlx_pixel_put(parsing.mlx_ptr, win_ptr, 10, 10, (255*255*255));
	mlx_loop(parsing.mlx_ptr);
	return (0);
}