/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_wall_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:50:26 by tdayde            #+#    #+#             */
/*   Updated: 2021/01/15 20:01:13 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	// CONCAT MUR  Y // SI sin(angle) != 0
t_xy_cub first_wall_horiz(double x_dir, double y_dir, int map_x, int map_y, int map[6][6], double x_pos, double y_pos)
{
	double x;
	int y;
//	double slope = y_dir / x_dir;
	t_xy_cub wall_horiz = {-1, -1};
	
	if (y_dir > 0 && y_pos != floor(y_pos))
		y = (int)y_pos + 1;
	else 
		y = (int)y_pos;
	if (fabs(y_dir) != 1)
		x = x_pos + (((double)y - y_pos) / (y_dir / x_dir));
	else 
		x = x_pos;
//	printf("sin_a = %f, cos_a = %.f, x = %f\n", sin_a, cos_a, x);

	printf("x = %f, y = %d, x_dir = %f, y_dir = %f, map_x = %d, map_y = %d, map[x][y] = %d\n", x, y, x_dir, y_dir, map_x, map_y, map[(int)x][y]);
	while ((x >= 0 && x <= map_x && y >= 0 && y <= map_y) && map[(int)x][y] != -1)
	{
		printf("Debut boucle : x = %f, y = %d, map[x][y] = %d\n", x, y, map[(int)x][y]);
		if ((y_dir > 0 && map[(int)x][y] == 1) || (y_dir < 0 && map[(int)x][y - 1] == 1))
		{
			wall_horiz.x = x;
			wall_horiz.y = y;
			return (wall_horiz);
		}
		//printf("cos(angle) = %.100f, x = %f\n", cos_a, x);
		// if (x_dir > 0.00000001)
		// 	x += 1 / (y_dir / x_dir);
		// else if (x_dir < -0.00000001) 
		//  	x -= 1 / (y_dir / x_dir);
		if (y_dir > 0)
			y += 1;
		else 
			y -= 1;
		if (fabs(y_dir) != 1)
			x = x_pos + (((double)y - y_pos) / (y_dir / x_dir));
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
	double distance;
	double x_pos = 1;
	// int test = x_pos / 1 + 1;
	// printf("Xa = %d\n", test);
	double y_pos = 5;
	double x_dir;
	double y_dir;
	double slope;
	int init;
	double conv = 180 / M_PI;
	double angle = (-45) / conv;
//	int square = 64;
	int map[map_x][map_y];
	t_xy_cub wall_horiz;

	double sin_a = sin(angle);
	
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
	
	x_dir = cos(angle);
	y_dir = sin(angle);

	// if (angle != 90 / conv && angle != -90 / conv)
	// 	slope = sin(angle) / cos(angle);
	// else 
	// 	slope = 0;
	
	printf("angle = %f, sin(angle) = %f, cos(angle) = %f\n", angle * 180/M_PI, y_dir, x_dir);
	if (fabs(x_dir) != 1)
//	if (sin(angle) != 0)
	{
		wall_horiz = first_wall_horiz(x_dir, y_dir, map_x, map_y, map, x_pos, y_pos);
		printf("fin first_wall_horiz : x = %.20f, y = %.20f\n", wall_horiz.x, wall_horiz.y);
		if (wall_horiz.x != -1)
		{
			distance = sqrt(pow(wall_horiz.y - y_pos, 2) + pow(wall_horiz.x - x_pos, 2));
			printf("distance horiz = %f, x = %f, y = %f\n", distance, wall_horiz.x - x_pos, wall_horiz.y - y_pos);
		}
	}


	return (wall_horiz);
}

int main()
{
	setbuf(stdout, NULL);
	find_wall_contact();
	return(0);
}