/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:35:41 by tdayde            #+#    #+#             */
/*   Updated: 2021/01/19 17:36:44 by tdayde           ###   ########lyon.fr   */
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

typedef struct	s_xy_cub
{
	double x;
	double y;
	double distance;
}				t_xy_cub;

typedef struct	s_wall_text
{
	char *wall_text_path;
	int *img;
	int w;
	int h;
}				t_wall_text;

typedef struct	s_info
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	int *img;
	int screen_w;
	int screen_h;
	int screen_d;
	int wall_col;
	t_wall_text wall_text;
	// int *wall_north_text;
	// int *wall_east_text;
	// int *wall_west_text;
	// int *wall_south_text;
	int floor_col;
	int sky_col;
	int map_w;
	int map_h;
	int **map;
	char *map_file;
	int wall_h;
	int player_h;
	double speed;
	double fov;
	double angle_per_pix;
	double pos_x;
	double pos_y;
	double angle;

}				t_pars;

// typedef struct	s_display
// {
// }

void modify_img(t_pars *pars);

#endif