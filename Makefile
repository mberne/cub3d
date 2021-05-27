SRCS		= main.c parsing_settings.c parsing_map.c utils.c events.c draw.c player.c ray.c plane.c wall.c texture.c my_mlx_functions.c

OBJS		= $(SRCS:.c=.o)

HEADER		= cub3d.h

NAME		= cub3D

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

LIBFT		= libft.a

LIBMLX		= libmlx.dylib

all bonus:	libs $(NAME)

$(NAME):	$(OBJS) $(LIBFT) $(LIBMLX)
			gcc $(CFLAGS) $(OBJS) $(LIBFT) $(LIBMLX) -o $(NAME) -I $(HEADER)

libs:
			$(MAKE) -C libft
			ln -sf libft/$(LIBFT) .
			$(MAKE) -C mlx
			ln -sf mlx/$(LIBMLX) .

%.o:		%.c	$(HEADER)
			gcc $(CFLAGS) -Imlx -c $< -o ${<:.c=.o} -I $(HEADER)


clean:
			${MAKE} clean -C libft
			${MAKE} clean -C mlx
			$(RM) $(OBJS)

fclean:		
			${MAKE} fclean -C libft
			${MAKE} clean -C mlx
			$(RM) $(OBJS) $(NAME) $(LIBFT) $(LIBMLX)

re:			fclean all

.PHONY:		all clean fclean re libs