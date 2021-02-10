/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:46:18 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/10 15:29:08 by tdayde           ###   ########lyon.fr   */
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
		mlx_put_image_to_window(pars->scr.mlx, pars->scr.win, pars->sprite.img_ptr, 0, 0);
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
	
	new = NULL;
	if ((new = malloc(sizeof(t_sprite) * (pars->nb_spr + 1))) == NULL)
		return (NULL);
	i = -1;
	while (++i < pars->nb_spr)
		new[i] = pars->spr[i];
	new[i].x = (double)x + 0.5;
	new[i].y = (double)y + 0.5;
	new[i].v_x = 0;
	new[i].v_y = 0;
	new[i].dst = 0;
	pars->nb_spr++;
	free(pars->spr);
	return (new);
}

int contouring_sprite(t_pars *pars)
{
	int ref;
	int x;
	int y;
	
	y = -1;
	ref = pars->sprite.img[0];
	while (++y < pars->sprite.h)
	{
		x = -1;
		while (++x < pars->sprite.h)
			if (pars->sprite.img[x + y * pars->sprite.s_l] == ref)
				pars->sprite.img[x + y * pars->sprite.s_l] = 0xff000000;
	}
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
	pars->moov.ang = 90;
	pars->moov.x_dir = cos(pars->moov.ang / (180 / M_PI));
	pars->moov.y_dir = sin(pars->moov.ang / (180 / M_PI));
	pars->moov.speed = 0.2;
	pars->map.map_file = file;
	pars->scr.w = 956;
	pars->scr.h = 600;

	if (!(create_all(pars)))
		return (-1);

	pars->wall_col = 0x00ff0000;
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

	if ((pars->map.map = malloc(sizeof(int*) * pars->map.map_h)) == NULL)
		return (-1);
	while (++i < pars->map.map_h)
		if ((pars->map.map[i] = malloc(sizeof(int) * pars->map.map_w)) == NULL)
			return (-1);
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
				if ((pars->spr = add_sprite(i, j, pars)) == NULL)
					return (-1);
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
	return (0);
}


int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_pars pars;

	setbuf(stdout, NULL);
	init_pars(&pars);
	if ((pars_map(&pars, argv[1]) == -1))
		exit (0);
	printf("pars.w = %d, pars.h = %d, pars.sl = %d\n", pars.scr.w, pars.scr.h, pars.scr.s_l);
//	contouring_sprite(&pars);
	modify_img(&pars);
	mlx_put_image_to_window(pars.scr.mlx, pars.scr.win, pars.scr.img_ptr, 0, 0);
	mlx_hook(pars.scr.win, 02, 1L<<0, show_key_code, &pars);
//	mlx_mouse_hook (pars.win, show_key_code, &pars);
	//mlx_pixel_put(pars->scr.mlx, win, 10, 10, (255*255*255));
	mlx_loop(pars.scr.mlx);
	return (0);
}