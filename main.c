/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:46:18 by tdayde            #+#    #+#             */
/*   Updated: 2021/01/19 17:37:03 by tdayde           ###   ########lyon.fr   */
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

void	set_map(t_pars *pars, int c)
{
	int i;
	int j;

	i = -1;
	while (++i < pars->map_h)
	{
		j = -1;
		while (++j < pars->map_w)
			pars->map[i][j] = c;
	}
}

int parsing_map(t_pars *pars, char *file)
{
	int i = -1, j = -1;
	pars->map_w = 0;
	pars->map_h = 1;
	pars->pos_x = 4;
	pars->pos_y = 5;
	pars->angle = -40;
	pars->speed = 0.5;
	pars->map_file = file;

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
	
	int fd = 0;
//	int ret = 1;
	char *line = NULL;
	int count_w = 0;
//	int count_h = 0;

	fd = open(pars->map_file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		count_w = 0;
		while (*line)
		{
			if (ft_isdigit(*line))
			{
				count_w++;	
				if (pars->map_w < count_w)
					pars->map_w++;
			}
			line++;
		}
		pars->map_h++;
	}
	close(fd);
//	printf("map_w = %d, map_h = %d\n", pars->map_w, pars->map_h);

	if ((pars->map = malloc(sizeof(int*) * pars->map_h)) == NULL)
		return (-1);
	while (++i < pars->map_h)
		if ((pars->map[i] = malloc(sizeof(int) * pars->map_w)) == NULL)
			return (-1);
	set_map(pars, -1);
	
	i = 0;
	int k;
	fd = open(pars->map_file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		k = -1;
		j = 0;
		while (line[++k])
		{
			if (line[k] != ' ')
				pars->map[i][j] = line[k] - '0'; 
			j++;
		}
		i++;
	}
	k = -1;
	j = 0;
	while (line[++k])
	{
		if (line[k] != ' ')
			pars->map[i][j] = line[k] - '0'; 
		j++;
	}
	
	i = -1;
	while (++i < pars->map_h)
	{
		j = -1;
		while (++j < pars->map_w)
		{
			if (pars->map[i][j] == -1)
				printf(" ");
			else
				printf("%d", pars->map[i][j]);
		}
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
	t_pars parsing = {0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0}, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
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
	parsing.wall_text.img = (int*)mlx_xpm_file_to_image(parsing.mlx_ptr, "./img_stone_wall.xpm", &parsing.wall_text.w, &parsing.wall_text.h);
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
//	mlx_mouse_hook (parsing.win_ptr, show_key_code, &parsing);
	//mlx_pixel_put(parsing.mlx_ptr, win_ptr, 10, 10, (255*255*255));
	mlx_loop(parsing.mlx_ptr);
	return (0);
}