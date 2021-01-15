/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:32:35 by tdayde            #+#    #+#             */
/*   Updated: 2021/01/15 18:08:52 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	// CONCAT MUR  Y // SI sin(angle) != 0
t_xy_cub first_wall_horiz(double slope, double angle, int map_x, int map_y, int map[6][6], double x_pos, double y_pos)
{
	double x;
	int y;
	double sin_a = sin(angle);
	double cos_a = cos(angle);
	double slope_abs = fabs(slope);
	t_xy_cub wall_horiz = {-1, -1};
	
	if (sin_a > 0 && y_pos != floor(y_pos))
		y = (int)y_pos + 1;
	else 
		y = (int)y_pos;
	if ((int)sin_a != 1 && (int)sin_a != -1)
		x = x_pos + (((double)y - y_pos) / slope);
	else 
		x = x_pos;
//	printf("sin_a = %f, cos_a = %.f, x = %f\n", sin_a, cos_a, x);

	printf("x = %f, y = %d, map_x = %d, map_y = %d, map[x][y] = %d\n", x, y, map_x, map_y, map[(int)x][y]);
	while ((x >= 0 && x <= map_x && y >= 0 && y <= map_y) && map[(int)x][y] != -1)
	{
		printf("Debut boucle : x = %f, y = %d, map[x][y] = %d, slope = %f\n", x, y, map[(int)x][y], slope);
		if (sin_a > 0 && map[(int)x][y] == 1)
		{
			wall_horiz.x = (int)x;
			wall_horiz.y = y;
			return (wall_horiz);
		}
		if (sin_a < 0 && map[(int)x][y - 1] == 1)
		{
			wall_horiz.x = (int)x;
			wall_horiz.y = y - 1;
			return (wall_horiz);
		}
		//printf("cos(angle) = %.100f, x = %f\n", cos_a, x);
		if (cos_a > 0.00000001)
			x += 1 / slope_abs;
		if (cos_a < -0.00000001) 
		 	x -= 1 / slope_abs;
		if (sin_a > 0)
			y += 1;
		else 
			y -= 1;
		//printf("Fin boucle : x = %f, y = %d, map[x][y] = %d, slope = %f\n", x, y, map[(int)x][y], slope);
	}
	return (wall_horiz);
}

t_xy_cub find_wall_contact()
{
	// double x;
	// double y;
	int map_x = 6;
	int map_y = 6;
	double x_pos = 3.5;
	// int test = x_pos / 1 + 1;
	// printf("Xa = %d\n", test);
	double y_pos = 3.5;
	// double x_dir;
	// double y_dir;
	double slope;
	int init;
	double conv = 180 / M_PI;
	double angle = 45 / conv;
//	int square = 64;
	int map[map_x][map_y];
	t_xy_cub wall_horiz;

	double sin_a = sin(angle);
	double cos_a = cos(angle);
	
	map[0][0] = 1;
	map[0][1] = 1;
	map[0][2] = 1;
	map[0][3] = 1;
	map[0][4] = 1;
	map[0][5] = 1;
	map[1][0] = 1;
	map[1][1] = 0;
	map[1][2] = 0;
	map[1][3] = 0;
	map[1][4] = 0;
	map[1][5] = 1;
	map[2][0] = 1;
	map[2][1] = 0;
	map[2][2] = 0;
	map[2][3] = 0;
	map[2][4] = 0;
	map[2][5] = 1;
	map[3][0] = 1;
	map[3][1] = 0;
	map[3][2] = 0;
	map[3][3] = 3;
	map[3][4] = 0;
	map[3][5] = 1;
	map[4][0] = 1;
	map[4][1] = 0;
	map[4][2] = 0;
	map[4][3] = 0;
	map[4][4] = 0;
	map[4][5] = 1;
	map[5][0] = 1;
	map[5][1] = 1;
	map[5][2] = 1;
	map[5][3] = 1;
	map[5][4] = 1;
	map[5][5] = 1;
	int i = -1;
	while (++i < 6)
	{
		int j = -1;
		while (++j < 6)
			printf("%d ", map[i][j]);
		printf("\n");
	}
	
	if (angle != 90 / conv && angle != -90 / conv)
		slope = sin(angle) / cos(angle);
	else 
		slope = 0;
	
	printf("sin(angle) = %.20f, cos(angle) = %.20f, (int)cos(angle) = %d\n", sin_a, cos(angle), (int)cos(angle));
	if (fabs(cos_a) != 1)
//	if (sin(angle) != 0)
	{
		wall_horiz = first_wall_horiz(slope, angle, map_x, map_y, map, x_pos, y_pos);
		printf("fin first_wall_horiz : x = %d, y = %d", wall_horiz.x, wall_horiz.y);
	}
	return (wall_horiz);
}

int main()
{
	setbuf(stdout, NULL);
	find_wall_contact();
	return(0);
}