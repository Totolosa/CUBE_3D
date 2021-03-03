NAME		= cub3D

SRCS		= 	main.c \
				cub3d.c \
				save.c \
				update_img.c \
				update_position.c \
				init_parsing.c \
				init_text.c \
				init_other.c \
				parsing_first_part.c \
				create_window_textures.c \
				create_map.c \
				fill_map.c \
				check_map.c \
				parsing_utils.c \
				ft_split_cub.c \
				raycasting.c \
				raycasting_utils.c \
				print_sky.c \
				print_wall.c \
				calcul_sprites.c \
				print_sprites.c \

srcs = $(addprefix srcs/, $(SRCS))

OBJS		= $(srcs:.c=.o)

CC          = gcc

CFLAGS      = -Wall -Werror -Wextra -fsanitize=address -g3

INCLUDE		= -Iinclude -I$(MINILIBX) -I$(LIBFT)/include

RM          = rm -f

LIBFT		= libft

MINILIBX	= minilibx_mms

COMP		= $(LIBFT)/libft.a libmlx.dylib

all:		comp $(NAME)

$(NAME): 	$(OBJS)
			$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -L $(LIBFT) -lft -L $(MINILIBX) -lmlx -o $(NAME)

$(OBJS):	$(COMP) include/cub3d.h 

comp:
			make -C $(LIBFT)
			make -C $(MINILIBX)

libmlx.dylib:
			make -C $(MINILIBX)
			cp minilibx_mms/libmlx.dylib .

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			$(RM) $(OBJS)
			make clean -C $(LIBFT)
			make clean -C $(MINILIBX)

fclean:		clean
			$(RM) $(NAME)
			$(RM) libmlx.dylib
			make fclean -C $(LIBFT)
			make fclean -C $(MINILIBX)

re:			fclean all

.PHONY: 	all comp clean fclean re comp
