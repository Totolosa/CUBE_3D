/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:56:25 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/15 18:17:16 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_map(t_pars *pars, int c)
{
	int i;
	int j;

	i = -1;
	while (++i < pars->map.map_h)
	{
		j = -1;
		while (++j < pars->map.map_w)
			pars->map.map[i][j] = c;
	}
}

t_sprite *add_sprite(int y, int x, t_pars *pars)
{
	t_sprite *new;
	int i;
	
	new = ft_alloc(sizeof(t_sprite) * (pars->nb_spr + 1), pars->free);
	i = -1;
	while (++i < pars->nb_spr)
		new[i] = pars->spr[i];
	new[i].x = (double)x + 0.5;
	new[i].y = (double)y + 0.5;
	new[i].x_dif = 0;
	new[i].y_dif = 0;
	new[i].v_dir = 0;
	new[i].v_per = 0;
	new[i].dst = 0;
	free(pars->spr);
	pars->nb_spr++;
	return (new);
}

int parsing(t_pars *pars, char *file)
{
	int i =-1, j = -1;
	int fd;
	int count_w;
	char *line;

	pars->moov.x_pos = 30;
	pars->moov.y_pos = 3;
	pars->moov.ang = 180;
	pars->moov.x_dir = cos(pars->moov.ang / (180 / M_PI));
	pars->moov.y_dir = sin(pars->moov.ang / (180 / M_PI));

	pars->map.map_file = file;
	parsing_first_part(pars);
	if (!(create_all(pars)))
		return (0);

	line = NULL;
	fd = open(pars->map.map_file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == ' ' || line[0] == '1' || line[0] == '2')
		{
			count_w = 0;
			while (*line)
			{
				if (ft_isdigit(*line))
				{
					count_w++;	
					if (pars->map.map_w < count_w)
						pars->map.map_w++;
				}
				line++;
			}
			pars->map.map_h++;
		}
	}
	pars->map.map_h++;
	close(fd);
	printf("map_w = %d, map_h = %d\n", pars->map.map_w, pars->map.map_h);

	//printf("map[y]\n");
	pars->map.map = ft_alloc(sizeof(int*) * pars->map.map_h, pars->free);
	while (++i < pars->map.map_h)
	{
		//printf("map[][x]\n");
		pars->map.map[i] = ft_alloc(sizeof(int) * pars->map.map_w, pars->free);
	}
	set_map(pars, -1);
	
	i = 0;
	int k;
	line[0] = 'A';
	fd = open(pars->map.map_file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == ' ' || line[0] == '1' || line[0] == '2')
		{
			k = -1;
			j = 0;
			while (line[++k])
			{
				if (line[k] != ' ')
					pars->map.map[i][j] = line[k] - '0';
				if (line[k] == '2')
					pars->spr = add_sprite(i, j, pars);
				j++;
			}
			i++;
		}
	}
	k = -1;
	j = 0;
	while (line[++k])
	{
		if (line[k] != ' ')
			pars->map.map[i][j] = line[k] - '0'; 
		j++;
	}
	close(fd);
	i = -1;
	while (++i < pars->map.map_h)
	{
		j = -1;
		while (++j < pars->map.map_w)
		{
			if (pars->map.map[i][j] == -1)
				printf(" ");
			else
				printf("%d", pars->map.map[i][j]);
		}
		printf("\n");
	}
	
	i = -1;
	while (++i < pars->nb_spr)
		printf("sprite %d : x = %f, y = %f\n", i + 1, pars->spr[i].x, pars->spr[i].y);
	printf("nb_spr = %d\n", pars->nb_spr);
	
	// fd = open("map.cub", O_RDONLY);
	// ret = 1;
	// while (ret > 0)
	// {
	// 	ret = get_next_line(fd, &line);
	// 	while (line[i])
	// 	{
	// 		if (line[i] == ' ')
	// 	}
	// }
	
//	printf("player_h = %d, angle/pixel = %f, tan(30) = %f, dst scr = %d\n", pars->player_h, pars->angle_per_pix, tan((pars->scr.fov / 2)), pars->h);
	return (1);
}