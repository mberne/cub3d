SRCS		= main.c parsing_settings.c parsing_map.c utils.c events.c draw.c player.c ray.c plane.c texture.c my_mlx_functions.c

OBJS		= $(SRCS:.c=.o)

HEADER		= cub3d.h

NAME		= cub3D

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

LIBFT		= libft.a

LIBMLX		= libmlx.dylib

%.o:		%.c	$(HEADER)
			gcc $(CFLAGS) -Imlx -c $< -o ${<:.c=.o} -I

$(NAME):	$(OBJS)
			$(MAKE) -C libft
			ln -sf libft/$(LIBFT) .
			$(MAKE) -C mlx
			ln -sf mlx/$(LIBMLX) .
			gcc $(CFLAGS) $(OBJS) $(LIBFT) $(LIBMLX) -o $(NAME)

all:		$(NAME)

clean:
			${MAKE} clean -C libft
			${MAKE} clean -C mlx
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(LIBFT)
			$(RM) $(LIBMLX)

re:			fclean all

.PHONY:		all clean fclean re