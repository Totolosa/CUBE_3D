/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:35:41 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/10 18:07:41 by tdayde           ###   ########lyon.fr   */
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
	double dst;
	char orient;
}				t_contact;

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
	double angle;
	double x_dir;
	double y_dir;
	double w_scr_h;
	double sky_h;
	int line;
}				t_ray;

typedef struct	s_print_text
{
	double	scale_h;
	double	scale_w;
	double	x_text;
	double	y_text;
}				t_print_text;

typedef struct	s_text
{
	char *path;
	void *img_ptr;
	int *img;
	int s_l;
	int w;
	int h;
	int endian;
	int bpp;
}				t_text;

typedef struct	s_screen
{
	void *mlx;
	void *win;
	int w;
	int h;
	int d;
	double fov;
	void *img_ptr;
	int *img;
	int s_l;
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
	t_screen scr;
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
	t_text no;
	t_text so;
	t_text we;
	t_text ea;
}				t_pars;

void modify_img(t_pars *pars);

void init_pars(t_pars *pars);
void init_t_ray(double angle, t_ray *ray);
int	create_all(t_pars *pars);

int find_wall_contact(t_ray *ray, t_pars *pars);
int horiz_or_verti(t_ray *ray, t_ray horiz, t_ray verti);
int continue_ray_verti(int x, double y, t_ray *verti, t_pars *pars);
int continue_ray_horiz(double x, int y, t_ray *horiz, t_pars *pars);

int print_wall_col(t_ray *ray, int x, t_pars *pars);

#endif