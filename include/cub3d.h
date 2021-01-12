/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:35:41 by tdayde            #+#    #+#             */
/*   Updated: 2021/01/12 19:43:56 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "libft.h"

typedef struct	s_info
{
	void *mlx_ptr;
	void *win_ptr;
	int player_h;
	int wall_h;
	int fov;
	int width_screen;
	int height_screen;
	int distance_screen;
	double angle_per_pix;
}				t_info;

#endif