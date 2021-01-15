/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:35:41 by tdayde            #+#    #+#             */
/*   Updated: 2021/01/15 19:17:44 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"

typedef struct	s_info
{
	void *mlx_ptr;
	void *win_ptr;
	double pos_x;
	double pos_y;
	int player_h;
	int wall_h;
	double fov;
	int width_screen;
	int height_screen;
	int distance_screen;
	double angle_per_pix;
}				t_info;

typedef struct	s_xy_cub
{
	double x;
	double y;
}				t_xy_cub;

#endif