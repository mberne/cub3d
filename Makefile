SRCS		= main.c

OBJS		= $(SRCS:.c=.o)

HEADER		= cub3d.h

NAME		= cub3d.a

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

.c.o:		$(HEADER)
			$(CC) $(CFLAGS) -Imlx -c $< -o ${<:.c=.o} -I

$(NAME):	$(OBJS)
			$(MAKE) -C libft
			cp libft/libft.a $(NAME)
			$(MAKE) -C mlx
			cp mlx/libmlx.dylib $(NAME)
			$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all:		$(NAME)

clean:
			${MAKE} clean -C libft
			${MAKE} clean -C mlx
			$(RM) $(OBJS)

fclean:		clean
			${MAKE} fclean -C libft
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re