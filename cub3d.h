#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft/includes/libft.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_settings
{
	char	*file;
	char	**tab;
	char	*line;
	int		res[2];
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*sprite;
	int		floor;
	int		ceiling;
	char	**map;
	int		mapx;
	int		mapy;
	int		pposition[2];
	char	porientation;
}	t_settings;

int				main(int ac, char **av);
void			init_struct(t_settings *set);
void			get_settings(t_settings *set);
void			parsing(t_settings *set, int fd);
int				check_arg(t_settings *set, int i);
void			get_resolution(t_settings *set);
void			get_texture(t_settings *set);
void			get_color(t_settings *set);
unsigned int	get_rgb(unsigned int r, unsigned int g, unsigned int b);
void			get_map(t_settings *set, int fd);
void			setup_map(t_settings *set);
void			check_map(t_settings *set);
int				check_wall(t_settings *set, int i, int j);
void			free_split(char **tab, int i);
int				number_of_split(char **tab);
int				ft_isnumber(char *s);
void			ft_exit(t_settings *set, char *str);

#endif
