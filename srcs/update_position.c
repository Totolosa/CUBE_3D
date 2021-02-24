/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 17:48:59 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/24 18:08:56 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_front_colision(t_pars *p)
{
	double	tmpx;
	double	tmpy;

	tmpx = p->moov.x_pos + p->moov.x_dir * p->moov.spd;
	tmpy = p->moov.y_pos + p->moov.y_dir * p->moov.spd;
	if (p->map.map[(int)tmpy][(int)p->moov.x_pos] != 1
		&& p->map.map[(int)tmpy][(int)p->moov.x_pos] != 2)
		p->moov.y_pos = tmpy;
	if (p->map.map[(int)p->moov.y_pos][(int)tmpx] != 1
		&& p->map.map[(int)p->moov.y_pos][(int)tmpx] != 2)
		p->moov.x_pos = tmpx;
	return (1);
}

int	check_back_colision(t_pars *p)
{
	double	tmpx;
	double	tmpy;

	tmpx = p->moov.x_pos - p->moov.x_dir * p->moov.spd;
	tmpy = p->moov.y_pos - p->moov.y_dir * p->moov.spd;
	if (p->map.map[(int)tmpy][(int)p->moov.x_pos] != 1
		&& p->map.map[(int)tmpy][(int)p->moov.x_pos] != 2)
		p->moov.y_pos = tmpy;
	if (p->map.map[(int)p->moov.y_pos][(int)tmpx] != 1
		&& p->map.map[(int)p->moov.y_pos][(int)tmpx] != 1)
		p->moov.x_pos = tmpx;
	return (1);
}

int	check_left_colision(t_pars *p)
{
	double	tmpx;
	double	tmpy;

	tmpx = p->moov.x_pos
		+ (cos((p->moov.ang - 90) / (180 / M_PI)) * p->moov.spd);
	tmpy = p->moov.y_pos
		+ (sin((p->moov.ang - 90) / (180 / M_PI)) * p->moov.spd);
	if (p->map.map[(int)tmpy][(int)p->moov.x_pos] != 1
		&& p->map.map[(int)tmpy][(int)p->moov.x_pos] != 2)
		p->moov.y_pos = tmpy;
	if (p->map.map[(int)p->moov.y_pos][(int)tmpx] != 1
		&& p->map.map[(int)p->moov.y_pos][(int)tmpx] != 2)
		p->moov.x_pos = tmpx;
	return (1);
}

int	check_right_colision(t_pars *p)
{
	double	tmpx;
	double	tmpy;

	tmpx = p->moov.x_pos
		+ (cos((p->moov.ang + 90) / (180 / M_PI)) * p->moov.spd);
	tmpy = p->moov.y_pos
		+ (sin((p->moov.ang + 90) / (180 / M_PI)) * p->moov.spd);
	if (p->map.map[(int)tmpy][(int)p->moov.x_pos] != 1
		&& p->map.map[(int)tmpy][(int)p->moov.x_pos] != 2)
		p->moov.y_pos = tmpy;
	if (p->map.map[(int)p->moov.y_pos][(int)tmpx] != 1
		&& p->map.map[(int)p->moov.y_pos][(int)tmpx] != 2)
		p->moov.x_pos = tmpx;
	return (1);
}

int	update_position(t_pars *p)
{
	if (p->key.go_front == 1)
		check_front_colision(p);
	if (p->key.go_back == 1)
		check_back_colision(p);
	if (p->key.go_left == 1)
		check_left_colision(p);
	if (p->key.go_right == 1)
		check_right_colision(p);
	return (0);
}
