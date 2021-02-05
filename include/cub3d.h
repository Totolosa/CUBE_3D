/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:35:41 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/05 18:10:02 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"

typedef struct	s_contact
{
	double x;
	double y;
	double distance;
	char orient;
}				t_contact;

// typedef struct	s_find_sprite
// {
// 	double ar;
// 	double br;
// 	double cr;
// 	double as;
// 	double bs;
// 	double cs;
// 	double xc;
// 	double yc;
// 	double xs;
// 	double ys;
// 	double vect;
// 	double len;
// 	double dist;
// }				t_find_sprite;

typedef struct	s_sprite
{
	double x;
	double y;
	double v_x;
	double v_y;
	double dst;
}				t_sprite;

typedef struct	s_ray
{
	t_contact wall;
	// t_contact *sprites;
	// int nb_sprites;
	double angle;
}				t_ray;

typedef struct	s_text
{
	char *path;
	void *img_ptr;
	int *img;
	int size_line;
	int w;
	int h;
	int endian;
	int bpp;
}				t_text;

typedef struct	s_screen
{
	void *mlx_ptr;
	void *win_ptr;
	int screen_w;
	int screen_h;
	int screen_d;
	double fov;
	void *img_ptr;
	int *img;
	int size_line;
	int endian;
	int bpp;
}				t_screen;

typedef struct	s_moov
{
	double x_pos;
	double y_pos;
	double ang;
	double x_dir;
	double y_dir;
	double ang_pix;
	double speed;
}				t_moov;

typedef struct	s_map
{
	char *map_file;
	int **map;
	int map_w;
	int map_h;
}				t_map;

typedef struct	s_free
{
	void *content;
	struct s_free *next;
}				t_free;

typedef struct	s_pars
{
	// -- MANAGE --
	t_free *free;
	// -- SCREEN --
	t_screen screen;
	// -- MAP --
	t_map map;
	// -- MOOVEMENT --
	t_moov moov;
	// -- SPRITES --
	t_sprite *spr;
	int nb_spr;
	// -- HEIGHT --
	int wall_h;
	int player_h;
	// -- COLORS / TEXTURES
	int sky_col;
	int floor_col;
	int wall_col;
	t_text wall;
	t_text sprite;
	// t_text *wall_north_text;
	// t_text *wall_east_text;
	// t_text *wall_west_text;
	// t_text *wall_south_text;
}				t_pars;

void modify_img(t_pars *pars);
void init_pars(t_pars *pars);
void init_t_ray(t_ray *ray);

#endif