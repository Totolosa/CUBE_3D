/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:35:41 by tdayde            #+#    #+#             */
/*   Updated: 2021/01/18 16:23:06 by tdayde           ###   ########lyon.fr   */
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
	int floor_col;
	int sky_col;
	int map_w;
	int map_h;
	int **map;
	int wall_h;
	int player_h;
	double speed;
	double fov;
	double angle_per_pix;
	double pos_x;
	double pos_y;
	double angle;

}				t_pars;

typedef struct	s_xy_cub
{
	double x;
	double y;
	double distance;
}				t_xy_cub;

void modify_img(t_pars *pars);

#endif