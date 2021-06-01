NAME		= cub3D

#Sources
PATH_SRCS	= srcs/
SRCS		= $(addprefix $(PATH_SRCS), main.c parsing_settings.c parsing_map.c utils.c events.c draw.c player.c ray.c plane.c wall.c texture.c my_mlx_functions.c minimap.c)

#Includes
PATH_INC	= includes/
HEADER		= $(addprefix $(PATH_INC), cub3d.h)

#Lib
LIBFT		= libft.a
LIBMLX		= libmlx.dylib

#Other
OBJS		= $(SRCS:.c=.o)
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

all bonus:	libs $(NAME)

$(NAME):	$(OBJS) $(LIBFT) $(LIBMLX)
			gcc $(CFLAGS) $(OBJS) $(LIBFT) $(LIBMLX) -o $(NAME) -I $(PATH_INC)

libs:
			$(MAKE) -C libft
			ln -sf libft/$(LIBFT) .
			$(MAKE) -C mlx
			ln -sf mlx/$(LIBMLX) .

%.o:		%.c	$(HEADER)
			gcc $(CFLAGS) -Imlx -c $< -o ${<:.c=.o} -I $(PATH_INC) -O3

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