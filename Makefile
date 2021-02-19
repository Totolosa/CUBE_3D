NAME		= cub3D

SRCS		= 	main.c \
				cub3d.c \
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
				print_wall.c \
				calcul_sprites.c \
				print_sprites.c \


OBJS		= $(SRCS:.c=.o)

CC          = gcc

CFLAGS      = -Wall -Werror -Wextra -fsanitize=address -g3

INCLUDE		= -Iinclude -I$(MINILIBX) -I$(LIBFT)/include

FRAMEWORK	= -framework OpenGL -framework AppKit

RM          = rm -f

LIBFT		= libft

MINILIBX	= minilibx_mms
#MINILIBX	= minilibx_opengl

COMP		= $(LIBFT)/libft.a libmlx.dylib
#COMP		= $(LIBFT)/libft.a $(MINILIBX)/libmlx.a

all:		comp $(NAME)

$(NAME): 	$(OBJS)
			$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -L $(LIBFT) -lft -L $(MINILIBX) -lmlx -o $(NAME)
#			$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(FRAMEWORK) -L $(LIBFT) -lft -L $(MINILIBX) -lmlx -o $(NAME)

comp:
			make -C $(LIBFT)
			make -C $(MINILIBX)
#			cp minilibx_mms/libmlx.dylib .

%.o:		%.c $(COMP) include/cub3d.h 
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: 	all comp clean fclean re
