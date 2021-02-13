/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:46:18 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/13 17:04:34 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int show_key_code(int key_code, t_pars *pars)
{	
	ft_putnbr_fd(key_code, 1);
	if (key_code == 53)
	{
		mlx_destroy_window(pars->scr.mlx, pars->scr.win );
		free(pars->map.map);
		exit(0);
	}
	if (key_code == 123)
	{
		pars->moov.ang -= 5;
		pars->moov.x_dir = cos(pars->moov.ang / (180 / M_PI));
		pars->moov.y_dir = sin(pars->moov.ang / (180 / M_PI));
		modify_img(pars);
		mlx_put_image_to_window(pars->scr.mlx, pars->scr.win, pars->scr.img_ptr, 0, 0);
	}
	if (key_code == 124)
	{
		pars->moov.ang += 5;
		pars->moov.x_dir = cos(pars->moov.ang / (180 / M_PI));
		pars->moov.y_dir = sin(pars->moov.ang / (180 / M_PI));
		modify_img(pars);
		mlx_put_image_to_window(pars->scr.mlx, pars->scr.win, pars->scr.img_ptr, 0, 0);
	}
	if (key_code == 13)
	{
		pars->moov.x_pos+= pars->moov.x_dir * pars->moov.speed;
		pars->moov.y_pos+= pars->moov.y_dir * pars->moov.speed;
		modify_img(pars);
		mlx_put_image_to_window(pars->scr.mlx, pars->scr.win, pars->scr.img_ptr, 0, 0);
	}
	if (key_code == 1)
	{
		pars->moov.x_pos-= pars->moov.x_dir * pars->moov.speed;
		pars->moov.y_pos-= pars->moov.y_dir * pars->moov.speed;
		modify_img(pars);
		mlx_put_image_to_window(pars->scr.mlx, pars->scr.win, pars->scr.img_ptr, 0, 0);
	}
	if (key_code == 0)
	{
		pars->moov.x_pos+= (cos((pars->moov.ang- 90) / (180 / M_PI)) * pars->moov.speed);
		pars->moov.y_pos+= (sin((pars->moov.ang- 90) / (180 / M_PI)) * pars->moov.speed);
		modify_img(pars);
		mlx_put_image_to_window(pars->scr.mlx, pars->scr.win, pars->scr.img_ptr, 0, 0);
	}
	if (key_code == 2)
	{
		pars->moov.x_pos+= (cos((pars->moov.ang+ 90) / (180 / M_PI)) * pars->moov.speed);
		pars->moov.y_pos+= (sin((pars->moov.ang+ 90) / (180 / M_PI)) * pars->moov.speed);
		modify_img(pars);
		mlx_put_image_to_window(pars->scr.mlx, pars->scr.win, pars->scr.img_ptr, 0, 0);
	}
	if (key_code == 17)
	{
		mlx_put_image_to_window(pars->scr.mlx, pars->scr.win, pars->spr_text.img_ptr, 0, 0);
	}
	return (0);
}

void	set_map(t_pars *pars, int c)
{
	int i;
	int j;

	i = -1;
	while (++i < pars->map.map_h)
	{
		j = -1;
		while (++j < pars->map.map_w)
			pars->map.map[i][j] = c;
	}
}

t_sprite *add_sprite(int y, int x, t_pars *pars)
{
	t_sprite *new;
	int i;
	
	printf("sprite %d\n", pars->nb_spr+1);
	new = ft_alloc(sizeof(t_sprite) * (pars->nb_spr + 1), pars);
	i = -1;
	while (++i < pars->nb_spr)
		new[i] = pars->spr[i];
	new[i].x = (double)x + 0.5;
	new[i].y = (double)y + 0.5;
	new[i].x_dif = 0;
	new[i].y_dif = 0;
	new[i].v_dir = 0;
	new[i].v_per = 0;
	new[i].dst = 0;
	free(pars->spr);
	pars->nb_spr++;
	return (new);
}

int contouring_sprite(t_pars *pars)
{
	// int ref;
	// int x;
	// int y;
	
	// y = -1;
	// printf("")
	pars->spr_text.contour = pars->spr_text.img[0];
	// ref = pars->spr_text.img[0];
	// while (++y < pars->spr_text.h)
	// {
	// 	x = -1;
	// 	while (++x < pars->spr_text.h)
	// 		if (pars->spr_text.img[x + y * pars->spr_text.s_l] == ref)
	// 			pars->spr_text.img[x + y * pars->spr_text.s_l] = 0xff000000;
	// }
	return (1);
}

int pars_map(t_pars *pars, char *file)
{
	int i = -1, j = -1;
	pars->map.map_w = 0;
	pars->map.map_h = 1;
	pars->moov.x_pos = 3;
//	pars->moov.x_pos= 10.498097;
	pars->moov.y_pos = 3;
//	pars->moov.y_pos= 5.456422;
	pars->moov.ang = 30;
	pars->moov.x_dir = cos(pars->moov.ang / (180 / M_PI));
	pars->moov.y_dir = sin(pars->moov.ang / (180 / M_PI));
	pars->moov.speed = 0.2;
	pars->map.map_file = file;
	pars->scr.w = 960;
	pars->scr.h = 600;

	if (!(create_all(pars)))
		return (0);

	pars->floor_col = 0x0000ff00;
	pars->sky_col = 0x000000ff;
	pars->scr.fov = 60;
	pars->wall_h = 64;
	pars->player_h = pars->wall_h / 2;
	pars->moov.ang_pix = pars->scr.fov / (double)pars->scr.w;
	pars->scr.d = ((double)pars->scr.w / 2) / tan((pars->scr.fov / 2) / (180 / M_PI));

	int fd = 0;
//	int ret = 1;
	char *line = NULL;
	int count_w = 0;
//	int count_h = 0;

	fd = open(pars->map.map_file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		count_w = 0;
		while (*line)
		{
			if (ft_isdigit(*line))
			{
				count_w++;	
				if (pars->map.map_w < count_w)
					pars->map.map_w++;
			}
			line++;
		}
		pars->map.map_h++;
	}
	close(fd);
//	printf("map_w = %d, map_h = %d\n", pars->map_w, pars->map_h);

	printf("map[y]\n");
	pars->map.map = ft_alloc(sizeof(int*) * pars->map.map_h, pars);
	while (++i < pars->map.map_h)
	{
		printf("map[][x]\n");
		pars->map.map[i] = ft_alloc(sizeof(int) * pars->map.map_w, pars);
	}
	set_map(pars, -1);
	
	i = 0;
	int k;
	fd = open(pars->map.map_file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		k = -1;
		j = 0;
		while (line[++k])
		{
			if (line[k] != ' ')
				pars->map.map[i][j] = line[k] - '0';
			if (line[k] == '2')
				pars->spr = add_sprite(i, j, pars);
			j++;
		}
		i++;
	}
	k = -1;
	j = 0;
	while (line[++k])
	{
		if (line[k] != ' ')
			pars->map.map[i][j] = line[k] - '0'; 
		j++;
	}
	
	i = -1;
	while (++i < pars->map.map_h)
	{
		j = -1;
		while (++j < pars->map.map_w)
		{
			if (pars->map.map[i][j] == -1)
				printf(" ");
			else
				printf("%d", pars->map.map[i][j]);
		}
		printf("\n");
	}
	
	i = -1;
	while (++i < pars->nb_spr)
		printf("sprite %d : x = %f, y = %f\n", i + 1, pars->spr[i].x, pars->spr[i].y);
	printf("nb_spr = %d\n", pars->nb_spr);
	
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
	
//	printf("player_h = %d, angle/pixel = %f, tan(30) = %f, dst scr = %d\n", pars->player_h, pars->angle_per_pix, tan((pars->scr.fov / 2)), pars->h);
	return (1);
}


int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_pars pars;

	setbuf(stdout, NULL);
	if (!init_pars(&pars))
		exit (0);
	if (!pars_map(&pars, argv[1]))
		exit (0);
	printf("screen.w = %d, screen.h = %d, screen.d = %f, screen.sl = %d\n", pars.scr.w, pars.scr.h, pars.scr.d, pars.scr.s_l);
	contouring_sprite(&pars);
	modify_img(&pars);
	mlx_put_image_to_window(pars.scr.mlx, pars.scr.win, pars.scr.img_ptr, 0, 0);
	mlx_hook(pars.scr.win, 02, 1L<<0, show_key_code, &pars);
//	mlx_mouse_hook (pars.win, show_key_code, &pars);
	//mlx_pixel_put(pars->scr.mlx, win, 10, 10, (255*255*255));
	mlx_loop(pars.scr.mlx);
	return (0);
}