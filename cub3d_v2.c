/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:32:35 by tdayde            #+#    #+#             */
/*   Updated: 2021/01/27 16:03:14 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	// CONCAT MUR  Y // SI sin(angle) != 0
t_xy_cub first_wall_horiz(t_pars *pars, double x_dir, double y_dir)
{
	double x;
	int y;
//	double slope = y_dir / x_dir;
	t_xy_cub wall_horiz = {-1, -1, -1, 'h'};
	
	if (y_dir > 0 && pars->pos_y != floor(pars->pos_y))
		y = (int)pars->pos_y + 1;
	else 
		y = (int)pars->pos_y;
	if (fabs(y_dir) != 1)
		x = pars->pos_x + (((double)y - pars->pos_y) / (y_dir / x_dir));
	else 
		x = pars->pos_x;
//	printf("sin_a = %f, cos_a = %.f, x = %f\n", sin_a, cos_a, x);

//	printf("x = %f, y = %d, x_dir = %f, y_dir = %f, pars->map_w = %d, pars->map_h = %d,pars->map[x][y] = %d\n", x, y, x_dir, y_dir, pars->map_w, pars->map_h,pars->map[(int)x][y]);
	while ((x >= 0 && x < pars->map_w && y >= 0 && y < pars->map_h) &&
			((y_dir > 0 && pars->map[y][(int)x] != -1) || (y_dir < 0 && pars->map[y - 1][(int)x] != -1)))
	{
//		printf("Debut boucle : x = %f, y = %d,pars->map[x][y] = %d\n", x, y,pars->map[(int)x][y]);
		if ((y_dir > 0 && pars->map[y][(int)x] == 1) || (y_dir < 0 && pars->map[y - 1][(int)x] == 1))
		{
			wall_horiz.x = x;
			wall_horiz.y = y;
			return (wall_horiz);
		}
		//printf("cos(angle) = %.100f, x = %f\n", cos_a, x);
		// if (x_dir > 0.00000001)
		// 	x += 1 / (y_dir / x_dir);
		// else if (x_dir < -0.00000001) 
		//  	x -= 1 / (y_dir / x_dir);
		if (y_dir > 0)
			y += 1;
		else 
			y -= 1;
		if (fabs(y_dir) != 1)
			x = pars->pos_x + (((double)y - pars->pos_y) / (y_dir / x_dir));
	//	printf("test bug map chelou\n");
	//	printf("Fin boucle Horizontale : x = %f, y = %d, map_w = %d\n", x, y, pars->map_w);
	//	printf("Fin boucle : x = %f, y = %d, pars->map[x][y] = %d\n", x, y,pars->map[(int)x][y]);
	}
	return (wall_horiz);
}

t_xy_cub first_wall_verti(t_pars *pars, double x_dir, double y_dir)
{
	int x;
	double y;
	t_xy_cub wall_verti = {-1, -1, -1, 'v'};
	
	if (x_dir > 0 && pars->pos_x != floor(pars->pos_x))
		x = (int)pars->pos_x + 1;
	else 
		x = (int)pars->pos_x;
	if (fabs(x_dir) != 1)
		y = pars->pos_y + (((double)x - pars->pos_x) * (y_dir / x_dir));
	else 
		y = pars->pos_y;
//	printf("sin_a = %f, cos_a = %.f, x = %f\n", sin_a, cos_a, x);

//	printf("x = %f, y = %d, x_dir = %f, y_dir = %f, pars->map_w = %d, pars->map_h = %d,pars->map[x][y] = %d\n", x, y, x_dir, y_dir, pars->map_w, pars->map_h,pars->map[(int)x][y]);
	while ((x >= 0 && x <= pars->map_w && y >= 0 && y <= pars->map_h) &&
			((x_dir > 0 && pars->map[(int)y][x] != -1) || (x_dir < 0 && pars->map[(int)y][x - 1] != -1)))
	{
//		printf("Debut boucle : x = %d, y = %f,pars->map[x][y] = %d\n", x, y,pars->map[x][(int)y]);
		if ((x_dir > 0 && pars->map[(int)y][x] == 1) || (x_dir < 0 && pars->map[(int)y][x - 1] == 1))
		{
			wall_verti.x = x;
			wall_verti.y = y;
			return (wall_verti);
		}
		//printf("cos(angle) = %.100f, x = %f\n", cos_a, x);
		// if (x_dir > 0.00000001)
		// 	x += 1 / (y_dir / x_dir);
		// else if (x_dir < -0.00000001) 
		//  	x -= 1 / (y_dir / x_dir);
		if (x_dir > 0)
			x += 1;
		else 
			x -= 1;
		if (fabs(x_dir) != 1)
			y = pars->pos_y + (((double)x - pars->pos_x) * (y_dir / x_dir));
		//printf("Fin boucle : x = %f, y = %d,pars->map[x][y] = %d, slope = %f\n", x, y,pars->map[(int)x][y], slope);
	}
	return (wall_verti);
}

t_xy_cub find_wall_contact(t_pars *pars, double angle)
{
	double distance_horiz = -1;
	double distance_verti = -1;
	double x_dir = cos(angle);
	double y_dir = sin(angle);
	t_xy_cub first_wall;
	t_xy_cub wall_horiz;
	t_xy_cub wall_verti;
	
//	printf("angle = %f, sin(angle) = %f, cos(angle) = %f\n", angle * 180/M_PI, y_dir, x_dir);
	if (fabs(x_dir) != 1)
//	if (sin(angle) != 0)
	{
		wall_horiz = first_wall_horiz(pars, x_dir, y_dir);
//		printf("fin first_wall_horiz : x = %.20f, y = %.20f\n", wall_horiz.x, wall_horiz.y);
		if (wall_horiz.x != -1)
		{
			distance_horiz = sqrt(pow(wall_horiz.y - pars->pos_y, 2) + pow(wall_horiz.x - pars->pos_x, 2));
//			printf("distance horiz = %f, x = %f, y = %f\n", distance_horiz, wall_horiz.x - pars->pos_x, wall_horiz.y - pars->pos_y);
		}
	}
	if (fabs(y_dir) != 1)
//	if (sin(angle) != 0)
	{
		wall_verti = first_wall_verti(pars, x_dir, y_dir);
//		printf("fin first_wall_verti : x = %.20f, y = %.20f\n", wall_verti.x, wall_verti.y);
		if (wall_verti.x != -1)
		{
			distance_verti = sqrt(pow(wall_verti.y - pars->pos_y, 2) + pow(wall_verti.x - pars->pos_x, 2));
//			printf("distance horiz = %f, x = %f, y = %f\n", distance_verti, wall_verti.x - pars->pos_x, wall_verti.y - pars->pos_y);
		}
	}

	if ((distance_horiz <= distance_verti && distance_horiz != -1) ||
			(distance_horiz >= distance_verti && distance_verti == -1))
	{
		first_wall.distance = distance_horiz;
		first_wall.x = wall_horiz.x;
		first_wall.y = wall_horiz.y;
		first_wall.orient = wall_horiz.orient;
	}
	else
	{
		first_wall.distance = distance_verti;
		first_wall.x = wall_verti.x;
		first_wall.y = wall_verti.y;
		first_wall.orient = wall_verti.orient;
	}
//	printf("dist_horiz = %f, dist_verti = %f, disance finale = %f\n", distance_horiz, distance_verti, first_wall.distance);
	angle = fabs((pars->angle / (180 / M_PI)) - angle);
//	printf("angle = %f\n", angle);
	first_wall.distance = cos(angle) * first_wall.distance; 
	return (first_wall);
}

int print_wall_texture(double wall_h_screen, int sky_h, int *line, t_xy_cub *wall, int *i, t_pars *pars)
{
	// (void)wall;
//	(void)sky_h;
	double scale_h = 0;
	double scale_w = 0;
	int j;
	double tmp1;
	double tmp2;
//	double percent;
	int start;
//	int line = 0;
//	double scale2 = 1;

	scale_h = (double)pars->wall_text->h / (double)wall_h_screen;
	tmp1 = scale_h;
	if (wall->orient == 'h')
		scale_w = modf(wall->x, &scale_w);
	else if (wall->orient == 'v')
		scale_w = modf(wall->y, &scale_w);
	j = scale_w * pars->wall_text->w;
	tmp2 = j;
	//printf("j = %d\n", j);
	if (wall_h_screen > pars->screen_h)
	{
	//	percent = ((double)wall_h_screen - (double)pars->screen_h) / 2 / (double)wall_h_screen;
		start = ((double)wall_h_screen - (double)pars->screen_h) / 2 / (double)wall_h_screen * (double)pars->wall_text->h;
		j += start * (double)pars->wall_text->size_line ;
	//	j += (wall_h_screen - pars->screen_h) / 2) / wall_h_screen * pars->wall_text->h * pars->wall_text->size_line ;
	//	printf("start = %d, j = %d, wall_h_screen = %f, i = %d, pars->screen_h = %d, pars->wall_text->h = %d, pars->wall_text->size_line = %d, pos_x = %f, pos_y = %f, angle = %f\n", start, j, wall_h_screen, *i, pars->screen_h, pars->wall_text->h, pars->wall_text->size_line, pars->pos_x, pars->pos_y, pars->angle);
	//	scale2 = pars->wall_text->h / pars->screen_h;
		tmp2 = j;
		wall_h_screen = pars->screen_h ;
	//	scale_h = 1 / scale_h; 
	}
//	printf("wall->orient = %c, scale_w = %f, j = %d, scale_h = %f\n", wall->orient, scale_w ,j ,scale_h);
	printf("i =  %d\n", *i / pars->size_line);

	while (*line < wall_h_screen + sky_h && j < pars->wall_text->h * pars->wall_text->size_line)
//	while (j < pars->wall_text->h * pars->wall_text->size_line)
	{
	//	printf("line = %d, wall_h_screen = %f, i = %d, scale_w = %f, scale_h = %f, j = %d, pars->wall_text->w = %d\n", *line, wall_h_screen, *i, scale_w, scale_h, j, pars->wall_text->w);
		pars->img[*i] = pars->wall_text->img[j];
	//	pars->img[*i] = pars->wall_col;
		*i += pars->size_line;
		scale_h += tmp1;
		j = tmp2 + ((int)scale_h * (pars->wall_text->size_line)) ;
	//	j = tmp2 + ((int)scale_h * scale2 * (pars->wall_text->size_line));
		(*line)++;
	//	printf("line wall = %d, i = %d\n", *line, *i);
	}
	
	return (1);
}

int print_col(t_xy_cub wall, int i, t_pars *pars)
{
	double wall_h_screen;
	int line;
	int sky_h;
//	int floor_h;

	wall_h_screen = (double)pars->screen_d / wall.distance;
	// if ((wall_h_screen = (double)pars->screen_d / wall.distance) % 2 == 1)
	// 	wall_h_screen += 0;
	if (wall_h_screen <= pars->screen_h)
	{
		sky_h = ((double)pars->screen_h - wall_h_screen) / 2;
		// if ((pars->screen_h - wall_h_screen) % 2 == 0)
		// 	floor_h = sky_h;
		// else 
		// 	floor_h = sky_h + 1;
	}
	else
	{
		sky_h = 0;
//		floor_h = 0;
	//	wall_h_screen = pars->screen_h;
	} 
//	printf("wall_h_screen + sky_floor_h / 2 = %d, sky_floor_h / 2 = %d\n", wall_h_screen + sky_floor_h / 2, sky_floor_h / 2);
//	printf("wall_d = %f, screen_d = %d\n", wall.distance, pars->screen_d);
//	printf("colonne = %d, wall_h_screen = %d, sky_floor_h = %d\n", count, wall_h_screen, sky_floor_h);
	line = 0;
	while (line < sky_h)
	{
		pars->img[i] = pars->sky_col;
		i += pars->size_line;
		line++;
//		printf("line sky = %d", line);
	}
//	line = -1;
	print_wall_texture(wall_h_screen, sky_h, &line, &wall, &i, pars);
	// while (line < wall_h_screen + sky_floor_h / 2)
	// {
	// 	pars->img[i] = pars->wall_col;
	// 	i += pars->screen_w;
	// 	line++;
//		printf("line wall = %d, ", line);
	// }
//	line += wall_h_screen;
	while (line < pars->screen_h)
	{
		pars->img[i] = pars->floor_col;
		i += pars->size_line;
		line++;
	//	printf("line floor = %d, ", line);
	}
	return (1);
}

void modify_img(t_pars *pars)
{
	t_xy_cub wall;
	double angle;
	int count;

	count = 0;
	angle = pars->angle - (pars->fov / 2);
	while (count < pars->screen_w)
	{
	//	printf("angle = %f\n", angle);
		wall = find_wall_contact(pars, angle / (180 / M_PI));
	//	printf("colonne = %d\n", count);
	//	printf("colonne = %d, wall.distance = %f\n", count, wall.distance);
		print_col(wall, count, pars);
		count++;
		angle += pars->angle_per_pix;
	}
}
