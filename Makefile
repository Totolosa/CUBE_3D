NAME		= cub3D

SRCS		= main.c cub3d.c

OBJS		= $(SRCS:.c=.o)

CC          = gcc

CFLAGS      = -Wall -Werror -Wextra

INCLUDE		= -Iinclude -I$(MINILIBX) -I$(LIBFT)/include

FRAMEWORK	= -framework OpenGL -framework AppKit

RM          = rm -f

LIBFT		= libft

MINILIBX	= minilibx

COMP		= $(LIBFT)/libft.a $(MINILIBX)/libmlx.a

all:		$(NAME)

$(NAME): 	$(COMP) $(OBJS)
			$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(FRAMEWORK) -L $(LIBFT) -lft -L $(MINILIBX) -lmlx -o $(NAME)

$(COMP):
			make -C $(LIBFT)
			make -C $(MINILIBX)

%.o:		%.c $(COMP) include/cub3d.h
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: 	all compilation clean fclean re
