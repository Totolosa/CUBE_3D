/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:46:18 by tdayde            #+#    #+#             */
/*   Updated: 2021/01/18 17:52:12 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int show_key_code(int key_code, t_pars *pars)
{	
	ft_putnbr_fd(key_code, 1);
	if (key_code == 53)
	{
		mlx_destroy_window(pars->mlx_ptr, pars->win_ptr );
		exit(0);
	}
	if (key_code == 123)
	{
		pars->angle -= 5;
		modify_img(pars);
		mlx_put_image_to_window(pars->mlx_ptr, pars->win_ptr, pars->img_ptr, 0, 0);
	}
	if (key_code == 124)
	{
		pars->angle += 5;
		modify_img(pars);
		mlx_put_image_to_window(pars->mlx_ptr, pars->win_ptr, pars->img_ptr, 0, 0);
	}
		if (key_code == 13)
	{
		pars->pos_x += (cos(pars->angle / (180 / M_PI)) * pars->speed);
		pars->pos_y += (sin(pars->angle / (180 / M_PI)) * pars->speed);
		modify_img(pars);
		mlx_put_image_to_window(pars->mlx_ptr, pars->win_ptr, pars->img_ptr, 0, 0);
	}
	if (key_code == 1)
	{
		pars->pos_x -= (cos(pars->angle / (180 / M_PI)) * pars->speed);
		pars->pos_y -= (sin(pars->angle / (180 / M_PI)) * pars->speed);
		modify_img(pars);
		mlx_put_image_to_window(pars->mlx_ptr, pars->win_ptr, pars->img_ptr, 0, 0);
	}
			if (key_code == 0)
	{
		pars->pos_x += (cos((pars->angle - 90) / (180 / M_PI)) * pars->speed);
		pars->pos_y += (sin((pars->angle - 90) / (180 / M_PI)) * pars->speed);
		modify_img(pars);
		mlx_put_image_to_window(pars->mlx_ptr, pars->win_ptr, pars->img_ptr, 0, 0);
	}
	if (key_code == 2)
	{
		pars->pos_x += (cos((pars->angle + 90) / (180 / M_PI)) * pars->speed);
		pars->pos_y += (sin((pars->angle + 90) / (180 / M_PI)) * pars->speed);
		modify_img(pars);
		mlx_put_image_to_window(pars->mlx_ptr, pars->win_ptr, pars->img_ptr, 0, 0);
	}
	return (0);
}

int parsing_map(t_pars *pars, char *file)
{
	(void)file;
	int i = -1, j = -1;
	pars->map_w = 6;
	pars->map_h = 6;
	pars->pos_x = 3.8;
	pars->pos_y = 3.9;
	pars->angle = 0;
	pars->speed = 0.1;

	pars->wall_col = 0x00ff0000;
	pars->floor_col = 0x0000ff00;
	pars->sky_col = 0x000000ff;
	pars->fov = 60;
	pars->screen_w = 960;
	pars->screen_h = 600;
	pars->wall_h = 64;
	pars->player_h = pars->wall_h / 2;
	pars->angle_per_pix = pars->fov / (double)pars->screen_w;
	pars->screen_d = ((double)pars->screen_w / 2) / tan((pars->fov / 2) / (180 / M_PI));
	
	// int fd;
	// int ret;
	// char *line;

	if ((pars->map = malloc(sizeof(int*) * pars->map_h)) == NULL)
		return (-1);
	while (++i < pars->map_h)
		if ((pars->map[i] = malloc(sizeof(int) * pars->map_w)) == NULL)
			return (-1);

	pars->map[0][0] = 1;
	pars->map[0][1] = 1;
	pars->map[0][2] = 1;
	pars->map[0][3] = 1;
	pars->map[0][4] = 1;
	pars->map[0][5] = 1;
	pars->map[1][0] = 1;
	pars->map[1][1] = 0;
	pars->map[1][2] = 0;
	pars->map[1][3] = 0;
	pars->map[1][4] = 0;
	pars->map[1][5] = 1;
	pars->map[2][0] = 1;
	pars->map[2][1] = 1;
	pars->map[2][2] = 1;
	pars->map[2][3] = 0;
	pars->map[2][4] = 0;
	pars->map[2][5] = 1;
	pars->map[3][0] = 1;
	pars->map[3][1] = 0;
	pars->map[3][2] = 0;
	pars->map[3][3] = 3;
	pars->map[3][4] = 0;
	pars->map[3][5] = 1;
	pars->map[4][0] = 1;
	pars->map[4][1] = 0;
	pars->map[4][2] = 0;
	pars->map[4][3] = 0;
	pars->map[4][4] = 0;
	pars->map[4][5] = 1;
	pars->map[5][0] = 1;
	pars->map[5][1] = 1;
	pars->map[5][2] = 1;
	pars->map[5][3] = 1;
	pars->map[5][4] = 1;
	pars->map[5][5] = 1;
	i = -1;
	while (++i < 6)
	{
		j = -1;
		while (++j < 6)
			printf("%d ", pars->map[i][j]);
		printf("\n");
	}
	// fd = open("map.cub", O_RDONLY);
	// ret = 1;
	// while (ret > 0)
	// {
	// 	ret = get_next_line(fd, &line);
	// 	while (line[i])
	// 	{
	// 		if (line[i] == ' ')
	// 	}
	// }
	
//	printf("player_h = %d, angle/pixel = %f, tan(30) = %f, distance screen = %d\n", pars->player_h, pars->angle_per_pix, tan((pars->fov / 2)), pars->screen_h);
	return (0);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_pars parsing = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int bpp;
	int size_line;
	int endian;
//	int i, j = 9;
	//int width, height;
	// void *mlx_ptr;
	// void *win_ptr;
	// void *img_wall_ptr;
	// char *img_wall;

	setbuf(stdout, NULL);

	if ((parsing_map(&parsing, argv[1]) == -1))
		exit (0);
	parsing.mlx_ptr = mlx_init();
	parsing.win_ptr = mlx_new_window(parsing.mlx_ptr, parsing.screen_w, parsing.screen_h, "CUB3D");
	parsing.img_ptr = mlx_new_image(parsing.mlx_ptr, parsing.screen_w, parsing.screen_h);
	parsing.img = (int*)mlx_get_data_addr(parsing.img_ptr, &bpp, &size_line, &endian);
	// img_wall_ptr = mlx_xpm_file_to_image(parsing.mlx_ptr, "img_stone_wall.xpm", &width, &height);
	// img_wall = mlx_get_data_addr(img_wall_ptr, &bpp, &size_line, &endian);
	modify_img(&parsing);
	// while (++j <= 50)
	// {
	// 	i = 9;
	// 	while (++i <= 50)
	// 		((int*)img)[(i) + (j * size_line / 4)] = 0x00ffffff;
	// }
	mlx_put_image_to_window(parsing.mlx_ptr, parsing.win_ptr, parsing.img_ptr, 0, 0);
	mlx_hook(parsing.win_ptr, 2, 1L<<0, show_key_code, &parsing);
	mlx_mouse_hook (parsing.win_ptr, show_key_code, &parsing);
	//mlx_pixel_put(parsing.mlx_ptr, win_ptr, 10, 10, (255*255*255));
	mlx_loop(parsing.mlx_ptr);
	return (0);
}