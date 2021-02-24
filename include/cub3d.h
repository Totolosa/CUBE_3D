/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:35:41 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/24 14:07:31 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

typedef struct s_key
{
	int	go_front;
	int	go_back;
	int	go_left;
	int	go_right;
	int	turn_left;
	int	turn_right;
	int	close;
}	t_key;

typedef struct s_contact
{
	double	x;
	double	y;
	double	dst;
	char	orient;
}	t_contact;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	x_dif;
	double	y_dif;
	double	v_dir;
	double	v_per;
	double	dst;
	double	cen_scr;
	double	r_scr;
	double	l_scr;
	double	dst_scr;
	double	w_scr;
	double	h_scr;
	double	scale_h;
	double	scale_w;
}	t_sprite;

typedef struct s_ray
{
	t_contact	wall;
	double		angle;
	double		x_dir;
	double		y_dir;
	double		x_dir_per;
	double		y_dir_per;
	double		w_scr_h;
	double		sky_h;
	int			line;
}	t_ray;

typedef struct s_print_text
{
	double	scale_h;
	double	scale_w;
	double	x;
	double	y;
}	t_print_text;

typedef struct s_print_sprite
{
	double	x_scr;
	double	y_scr;
	double	x_spr;
	double	y_spr;
}	t_print_sprite;

typedef struct s_text
{
	char	*path;
	void	*img_ptr;
	int		*img;
	int		s_l;
	int		w;
	int		h;
	int		endian;
	int		bpp;
	int		cont;
}	t_text;

typedef struct s_screen
{
	void	*mlx;
	void	*win;
	int		w;
	int		h;
	int		real_w;
	int		real_h;
	double	d;
	double	fov;
	void	*img_ptr;
	int		*img;
	int		s_l;
	int		endian;
	int		bpp;
}	t_screen;

typedef struct s_moov
{
	double	x_pos;
	double	y_pos;
	double	ang;
	double	x_dir;
	double	y_dir;
	double	ang_pix;
	double	spd;
}	t_moov;

typedef struct s_map
{
	char	*map_file;
	int		**map;
	int		map_w;
	int		map_h;
}	t_map;

typedef struct s_pars
{
	t_list		*free;
	t_key		key;
	t_screen	scr;
	t_map		map;
	t_moov		moov;
	t_sprite	*spr;
	int			nb_spr;
	double		*w_dst_col;
	int			wall_h;
	int			player_h;
	int			sky_col;
	int			floor_col;
	t_text		spr_text;
	t_text		no;
	t_text		so;
	t_text		we;
	t_text		ea;
}	t_pars;

int		modify_img(t_pars *pars);
int		update_img(t_pars *pars);
int		close_window(t_pars *pars);
int		save_bmp(const char *filename, t_pars *pars);
int		key_press(int key, t_pars *pars);
int		key_release(int key, t_pars *pars);

int		init_pars(t_pars *pars);
int		parsing(t_pars *pars, char *file);
int		parsing_first_part(char *file, t_pars *pars);
int		create_window_textures(t_pars *pars);
int		create_map(t_pars *pars, int c);
int		fill_map(t_pars *pars);
int		check_map(t_pars *pars);
int		is_closed(int ***copy, int x, int y, t_pars *pars);
int		start_browse_file(int *ret, char **line, int fd, t_pars *pars);
char	*ft_strtrim_cub(char const *s1, char const *set, t_pars *pars);
char	**ft_split_cub(char const *s, char c, t_pars *pars);
int		quit_prog(char *str, t_pars *pars);

int		init_t_ray(double angle, t_ray *ray);
int		find_wall_contact(t_ray *ray, t_pars *pars);
int		horiz_or_verti(t_ray *ray, t_ray horiz, t_ray verti);
int		continue_ray_verti(int x, double y, t_ray *verti, t_pars *pars);
int		continue_ray_horiz(double x, int y, t_ray *horiz, t_pars *pars);

int		init_print_text(t_print_text *text);
int		print_wall_col(t_ray *ray, int x, t_pars *pars);

int		init_new_sprite(t_sprite *sprite);
int		calcul_h_sprite(t_pars *p);
int		print_sprites(t_pars *pars);

#endif