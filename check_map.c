/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:21:15 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/18 16:52:03 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_valid_char(t_pars *p)
{
	int	i;
	int	j;
	int	c;
	int	position;

	position = 0;
	i = -1;
	while (++i < p->map.map_h)
	{
		j = -1;
		while (++j < p->map.map_w)
		{	
			c = p->map.map[i][j];
			if (c != -1 && c != 0 && c != 1 && c != 2
				&& c != 'N' && c != 'S' && c != 'W' && c != 'E')
				quit_prog(p);
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
				position++;
			if (position == 2
				|| (i == p->map.map_h && j == p->map.map_w && position == 0))
				quit_prog(p);
		}
	}
	return (1);
}

int	check_square(int ***copy, int x, int y, t_pars *pars)
{
	if (pars->map.map[y][x] == -1)
		quit_prog(pars);
	else if (pars->map.map[y][x] == 1)
	{
		(*copy)[y][x] = 1;
		return (1);
	}
	else
	{
		(*copy)[y][x] = 1;
		is_closed(copy, x, y, pars);
	}
	return (1);
}

int	is_on_map(int x, int y, t_pars *pars)
{
	if (x < 0 || y < 0 || x >= pars->map.map_w || y >= pars->map.map_h)
		quit_prog(pars);
	return (1);
}

int	is_closed(int ***copy, int x, int y, t_pars *pars)
{
	if (is_on_map(x + 1, y, pars) && (*copy)[y][x + 1] == 0)
		check_square(copy, x + 1, y, pars);
	if (is_on_map(x + 1, y + 1, pars) && (*copy)[y + 1][x + 1] == 0)
		check_square(copy, x + 1, y + 1, pars);
	if (is_on_map(x, y + 1, pars) && (*copy)[y + 1][x] == 0)
		check_square(copy, x, y + 1, pars);
	if (is_on_map(x - 1, y + 1, pars) && (*copy)[y + 1][x - 1] == 0)
		check_square(copy, x - 1, y + 1, pars);
	if (is_on_map(x - 1, y, pars) && (*copy)[y][x - 1] == 0)
		check_square(copy, x - 1, y, pars);
	if (is_on_map(x - 1, y - 1, pars) && (*copy)[y - 1][x - 1] == 0)
		check_square(copy, x - 1, y - 1, pars);
	if (is_on_map(x, y - 1, pars) && (*copy)[y - 1][x] == 0)
		check_square(copy, x, y - 1, pars);
	if (is_on_map(x + 1, y - 1, pars) && (*copy)[y - 1][x + 1] == 0)
		check_square(copy, x + 1, y - 1, pars);
	return (1);
}

int	check_map(t_pars *pars)
{
	int	x;
	int	y;
	int	**copy;

	check_valid_char(pars);
	copy = ft_alloc(sizeof(int*) * pars->map.map_h, pars->free);
	y = -1;
	while (++y < pars->map.map_h)
		copy[y] = ft_alloc(sizeof(int) * pars->map.map_w, pars->free);
	y = -1;
	while (++y < pars->map.map_h)
	{
		x = -1;
		while (++x < pars->map.map_w)
			copy[y][x] = 0;
	}
	x = pars->moov.x_pos - 0.5;
	y = pars->moov.y_pos - 0.5;
	is_closed(&copy, x, y, pars);
	return (1);
}
