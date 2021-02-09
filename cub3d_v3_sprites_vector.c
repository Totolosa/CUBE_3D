/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_v3_sprites_vector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:32:35 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/09 15:10:03 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int calcul_distance_sprite(t_pars *pars)
{
	(void)pars;
	int i;

	i = -1;
	while (++i < pars->nb_spr)
	{
		pars->spr[i].v_x = pars->spr[i].x - pars->moov.x_pos;
		pars->spr[i].v_x = pars->spr[i].y - pars->moov.y_pos;
//		pars->spr[i].dst = pars->spr[i]v_x * cos()
	}
	return (1);
}

// int add_sprite(int x, int y, t_ray *ray, t_pars *pars)
// {
// 	//printf("test\n");
// 	if ((ray->sprites = malloc(sizeof(t_contact) * (ray->nb_sprites + 1))) == NULL)
// 		return (0);
// 	ray->sprites[ray->nb_sprites].x = x;
// 	ray->sprites[ray->nb_sprites].y = y;
// 	ray->sprites[ray->nb_sprites].distance = sqrt(pow(y - pars->moov.y_pos, 2) + pow(x - pars->moov.x_pos, 2));
// 	ray->sprites[ray->nb_sprites].orient = 'h';
// 	ray->nb_sprites++;
// 	return (1);
// }

// int total_sprites(t_ray *ray, t_ray horiz, t_ray verti)
// {
// 	int i = 0;
// 	int j = 0;
// 	int k = 0;

// 	if (!(ray->sprites = malloc(sizeof(t_contact) * ray->nb_sprites)))
// 		return (0);
// 	while (++k < ray->nb_sprites)
// 	{
// 		if (horiz.sprites[i].distance < verti.sprites[j].distance)
// 		{
// 			ray->sprites[k] = horiz.sprites[i];
// 			i++;
// 		}
// 		else
// 		{
// 			ray->sprites[k] = verti.sprites[j];
// 			j++;
// 		}
// 	}
// 	return (1);
// }

	// CONCAT MUR  Y // SI sin(angle) != 0
int first_wall_horiz(t_ray *horiz, t_pars *pars, double x_dir, double y_dir)
{
	double x;
	int y;
	if (pars->moov.y_dir > 0)
		horiz->wall.orient = 's';
	else 
		horiz->wall.orient = 'n';
	
	if (y_dir > 0 && pars->moov.y_pos != floor(pars->moov.y_pos))
		y = (int)pars->moov.y_pos + 1;
	else 
		y = (int)pars->moov.y_pos;
	if (fabs(y_dir) != 1)
		x = pars->moov.x_pos + (((double)y - pars->moov.y_pos) / (y_dir / x_dir));
	else 
		x = pars->moov.x_pos;

	while ((x >= 1 && x < pars->map.map_w && y >= 1 && y < pars->map.map_h) &&
			((y_dir > 0 && pars->map.map[y][(int)x] != -1) || (y_dir < 0 && pars->map.map[y - 1][(int)x] != -1)))
	{
		// if ((y_dir > 0 && pars->map[y][(int)x] == 2) || (y_dir < 0 && pars->map[y - 1][(int)x] == 2))
		// 	add_sprite(x, y, horiz, pars);
		if ((y_dir > 0 && pars->map.map[y][(int)x] == 1) || (y_dir < 0 && pars->map.map[y - 1][(int)x] == 1))
		{
			horiz->wall.x = x;
			horiz->wall.y = y;
			horiz->wall.distance = sqrt(pow(horiz->wall.y - pars->moov.y_pos, 2) + pow(horiz->wall.x - pars->moov.x_pos, 2));
			return (1);
		}
		if (y_dir > 0)
			y += 1;
		else 
			y -= 1;
		if (fabs(y_dir) != 1)
			x = pars->moov.x_pos + (((double)y - pars->moov.y_pos) / (y_dir / x_dir));
	}
	return (1);
}

int first_wall_verti(t_ray *verti, t_pars *pars, double x_dir, double y_dir)
{
	int x;
	double y;
	if (pars->moov.x_dir > 0)
		verti->wall.orient = 'e';
	else 
		verti->wall.orient = 'w';
	
	if (x_dir > 0 && pars->moov.x_pos != floor(pars->moov.x_pos))
		x = (int)pars->moov.x_pos + 1;
	else 
		x = (int)pars->moov.x_pos;
	if (fabs(x_dir) != 1)
		y = pars->moov.y_pos + (((double)x - pars->moov.x_pos) * (y_dir / x_dir));
	else 
		y = pars->moov.y_pos;
//	printf("sin_a = %f, cos_a = %.f, x = %f\n", sin_a, cos_a, x);

//	printf("x = %f, y = %d, x_dir = %f, y_dir = %f, pars->map_w = %d, pars->map_h = %d,pars->map[x][y] = %d\n", x, y, x_dir, y_dir, pars->map_w, pars->map_h,pars->map[(int)x][y]);
	while ((x >= 1 && x < pars->map.map_w && y >= 1 && y < pars->map.map_h) &&
			((x_dir > 0 && pars->map.map[(int)y][x] != -1) || (x_dir < 0 && pars->map.map[(int)y][x - 1] != -1)))
	{
	//	printf("Debut boucle : x = %d, y = %f,pars->map[x][y] = %d\n", x, y,pars->map[x][(int)y]);
		// if ((x_dir > 0 && pars->map[(int)y][x] == 2) || (x_dir < 0 && pars->map[(int)y][x - 1] == 2))
		// 	add_sprite(x, y, verti, pars);
		if ((x_dir > 0 && pars->map.map[(int)y][x] == 1) || (x_dir < 0 && pars->map.map[(int)y][x - 1] == 1))
		{
			verti->wall.x = x;
			verti->wall.y = y;
			verti->wall.distance = sqrt(pow(verti->wall.y - pars->moov.y_pos, 2) + pow(verti->wall.x - pars->moov.x_pos, 2));
			return (1);
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
			y = pars->moov.y_pos + (((double)x - pars->moov.x_pos) * (y_dir / x_dir));
		//printf("Fin boucle : x = %f, y = %d,pars->map[x][y] = %d, slope = %f\n", x, y,pars->map[(int)x][y], slope);
	//	printf("fin boucle : x = %d, y = %f, x_dir = %f\n", x, y, x_dir);
	}
	return (1);
}

int find_wall_contact(t_ray *ray, t_pars *pars, double angle)
{
	// double distance_horiz = -1;
	// double distance_verti = -1;
	double x_dir = cos(angle);
	double y_dir = sin(angle);

	t_ray horiz;
	t_ray verti;

	init_t_ray(&horiz);
	init_t_ray(&verti);
//	printf("test\n");
	

	if (fabs(x_dir) != 1)
//	if (sin(angle) != 0)
	{
		if (!first_wall_horiz(&horiz, pars, x_dir, y_dir))
			return (0);
//		printf("fin first_wall_horiz : x = %.20f, y = %.20f\n", horiz.x, horiz.y);
// 		if (horiz->wall->x != -1)
// 		{
// 			distance_horiz = sqrt(pow(horiz->wall->y - pars->moov.y_pos, 2) + pow(horiz->wall->x - pars->moov.x_pos, 2));
// //			printf("distance horiz = %f, x = %f, y = %f\n", distance_horiz, horiz.x - pars->moov.x_pos, horiz.y - pars->moov.y_pos);
// 		}
	}
	if (fabs(y_dir) != 1)
//	if (sin(angle) != 0)
	{
		if(!first_wall_verti(&verti, pars, x_dir, y_dir))
			return (0);
//		printf("fin first_wall_verti : x = %.20f, y = %.20f\n", verti.x, verti.y);
// 		if (horiz->wall->x != -1)
// 		{
// 			distance_verti = sqrt(pow(verti->wall->y - pars->moov.y_pos, 2) + pow(verti->wall->x - pars->moov.x_pos, 2));
// //			printf("distance horiz = %f, x = %f, y = %f\n", distance_verti, verti.x - pars->moov.x_pos, verti.y - pars->moov.y_pos);
// 		}
	}

	if (horiz.wall.distance <= verti.wall.distance)
	{
		ray->wall.distance = horiz.wall.distance;
		ray->wall.x = horiz.wall.x;
		ray->wall.y = horiz.wall.y;
		ray->wall.orient = horiz.wall.orient;
	}
	else
	{
		ray->wall.distance = verti.wall.distance;
		ray->wall.x = verti.wall.x;
		ray->wall.y = verti.wall.y;
		ray->wall.orient = verti.wall.orient;
	}
//	printf("dist_horiz = %f, dist_verti = %f, disance finale = %f\n", distance_horiz, distance_verti, first_wall.distance);
	// ray->nb_sprites = horiz.nb_sprites + verti.nb_sprites;
	// if (ray->nb_sprites > 0)
	// 	total_sprites(ray, horiz, verti);
	angle = fabs((pars->moov.ang/ (180 / M_PI)) - angle);
	ray->wall.distance = cos(angle) * ray->wall.distance;

	return (1);
}

int print_wall_texture(double wall_h_screen, double sky_h, int *x, int *y, t_ray *ray, t_pars *pars)
{
	// (void)wall;
//	(void)sky_h;
	double scale_h = 0;
	double scale_w = 0;
	double x_text = 0;
	double y_text = 0;

	scale_h = (double)pars->wall.h / (double)wall_h_screen;
	if (ray->wall.orient == 'n' || ray->wall.orient == 's')
		scale_w = modf(ray->wall.x, &scale_w);
	else if (ray->wall.orient == 'w' || ray->wall.orient == 'e')
		scale_w = modf(ray->wall.y, &scale_w);
	x_text = scale_w * (double)pars->wall.w;

	if (wall_h_screen > pars->scr.h)
	{
		y_text = ((double)wall_h_screen - (double)pars->scr.h) / 2 / (double)wall_h_screen * (double)pars->wall.h;
		wall_h_screen = pars->scr.h;
	}
//	printf("wall->orient = %c, scale_w = %f, j = %d, scale_h = %f\n", wall->orient, scale_w ,j ,scale_h);
//	printf("x = %d, x_text = %f, y = %d, y_text = %f, wall_h_screen = %f, sky_h = %f, scale_w = %f, scale_h = %f, pars->h = %d, pars->wall_text->size_l = %d, pos_x = %f, pos_y = %f, angle = %f\n", *x, x_text, *y, y_text, wall_h_screen, sky_h, scale_w, scale_h, pars->wall_text->h, pars->wall_text->size_l, pars->moov.x_pos, pars->moov.y_pos, pars->angle);


	while (*y < wall_h_screen + sky_h)
	{
	//	printf("x = %d, x_text = %f, y = %d, y_text = %f, wall_h_screen = %f, scale_w = %f, scale_h = %f, pars->wall_text->w = %d\n", *x, x_text, *y, y_text, wall_h_screen, scale_w, scale_h, pars->wall_text->w);
		pars->scr.img[*x + *y * pars->scr.size_l] = pars->wall.img[(int)x_text + ((int)y_text * pars->wall.size_l)];
	//	pars->img[*x + *y * pars->size_l] = pars->wall_col;
	//	scale_h += tmp;
		y_text += scale_h;
	//	j = tmp2 + ((int)scale_h * scale2 * (pars->wall_text->size_l));
		(*y)++;
	//	printf("line wall = %d, i = %d\n", *line, *i);
	}
	
	return (1);
}

int print_col(t_ray *ray, int x, t_pars *pars)
{
	double wall_h_screen;
	double sky_h;
	int y;
//	int floor_h;

	wall_h_screen = (double)pars->scr.d / ray->wall.distance;
	// if ((wall_h_screen = (double)pars->d / wall.distance) % 2 == 1)
	// 	wall_h_screen += 0;
	if (wall_h_screen <= pars->scr.h)
	{
		sky_h = ((double)pars->scr.h - wall_h_screen) / 2;
		// if ((pars->h - wall_h_screen) % 2 == 0)
		// 	floor_h = sky_h;
		// else 
		// 	floor_h = sky_h + 1;
	}
	else
	{
		sky_h = 0;
//		floor_h = 0;
	//	wall_h_screen = pars->h;
	} 
//	printf("wall_h_screen + sky_floor_h / 2 = %d, sky_floor_h / 2 = %d\n", wall_h_screen + sky_floor_h / 2, sky_floor_h / 2);
//	printf("wall_d = %f, d = %d\n", wall.distance, pars->d);
//	printf("colonne = %d, wall_h_screen = %d, sky_floor_h = %d\n", count, wall_h_screen, sky_floor_h);
	y = 0;
	while (y < sky_h)
	{
		pars->scr.img[x + y * pars->scr.size_l] = pars->sky_col;
		y++;
//		printf("y sky = %d", y);
	}
//	y = -1;
	print_wall_texture(wall_h_screen, sky_h, &x, &y, ray, pars);
	// while (y < wall_h_screen + sky_floor_h / 2)
	// {
	// 	pars->img[i] = pars->wall_col;
	// 	i += pars->w;
	// 	y++;
//		printf("y wall = %d, ", y);
	// }
//	y += wall_h_screen;
	while (y < pars->scr.h)
	{
		pars->scr.img[x + y * pars->scr.size_l] = pars->floor_col;
		y++;
	//	printf("y floor = %d, ", y);
	}
	return (1);
}

void modify_img(t_pars *pars)
{
	t_ray ray;
	double angle;
	int i;

	init_t_ray(&ray);
	i = 0;
	angle = pars->moov.ang- (pars->scr.fov / 2);
	while (i < pars->scr.w)
	{
	//	printf("angle = %f\n", angle);
		find_wall_contact(&ray, pars, angle / (180 / M_PI));
	//	printf("colonne = %d, nb_sprite = %d\n", count, ray.nb_sprites);
	//	printf("colonne = %d, wall.distance = %f\n", count, wall.distance);
		print_col(&ray, i, pars);
		i++;
		angle = pars->moov.ang- (pars->scr.fov / 2) + pars->moov.ang_pix * (i + 1);
	}
	if (pars->nb_spr > 0)
	{
		calcul_distance_sprite(pars);
	}
}
