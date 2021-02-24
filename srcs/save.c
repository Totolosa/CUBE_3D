/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 15:48:28 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/23 16:31:02 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned char	*create_bitmap_file_header(int file_size)
{
	static unsigned char	file_header[] = {
		0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};

	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(14 + 40);
	return (file_header);
}

unsigned char	*create_bitmap_info_header(t_pars *pars)
{
	static unsigned char	info_header[] = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0,
		0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};

	info_header[0] = (unsigned char)(40);
	info_header[4] = (unsigned char)(pars->scr.w >> 0);
	info_header[5] = (unsigned char)(pars->scr.w >> 8);
	info_header[6] = (unsigned char)(pars->scr.w >> 16);
	info_header[7] = (unsigned char)(pars->scr.w >> 24);
	info_header[8] = (unsigned char)(pars->scr.h >> 0);
	info_header[9] = (unsigned char)(pars->scr.h >> 8);
	info_header[10] = (unsigned char)(pars->scr.h >> 16);
	info_header[11] = (unsigned char)(pars->scr.h >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(pars->scr.bpp);
	return (info_header);
}

void	write_img(int fd, t_pars *p)
{
	int	x;
	int	y;

	y = -1;
	while (++y < p->scr.h)
	{
		x = -1;
		while (++x < p->scr.w)
			write(fd, p->scr.img + x + (p->scr.h - y - 1) * p->scr.s_l, 4);
	}
}

int	save_bmp(const char *filename, t_pars *pars)
{
	int	fd;
	int	img_size;
	int	file_size;

	img_size = pars->scr.w * pars->scr.h * 4;
	file_size = img_size + (40 + 14);
	fd = open(filename, O_RDONLY | O_CREAT, S_IRWXU);
	if (fd < 0)
		quit_prog("fct open() save.c 1 failed\n", pars);
	close(fd);
	fd = open(filename, O_RDWR);
	if (fd < 0)
		quit_prog("fct open() save.c 2 failed\n", pars);
	write(fd, create_bitmap_file_header(file_size), 14);
	write(fd, create_bitmap_info_header(pars), 40);
	write_img(fd, pars);
	close(fd);
	ft_putstr_fd("Image generated!!\n", 1);
	return (1);
}
