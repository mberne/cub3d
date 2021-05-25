#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft/includes/libft.h"

# define W 13
# define S 1
# define A 0
# define D 2
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define SPACE 49
# define CROUCH 261
# define ESC 53
# define FOV 60

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

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

typedef struct s_plane
{
	float	a;
	float	b;
	float	c;
	float	d;
	int		direction;
}	t_plane;

typedef struct s_planes
{
	t_plane	*plane;
	int		num_wall;
	int		num_plane;
}	t_planes;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_intersection
{
	float		t;
	int			target_plane;
	t_vector	new_ray;
}	t_intersection;

typedef struct s_rays
{
	t_vector		*ray;
	t_intersection	*inter;
	int				num_r;
	float			rv;
}	t_rays;

typedef struct s_player
{
	float	x;
	float	y;
	float	z;
	float	rad;
}	t_player;

typedef struct s_key
{
	int	t_left;
	int	t_right;
	int	front;
	int	back;
	int	left;
	int	right;
	int	space;
	int	crouch;
}	t_key;

typedef struct s_textures
{
	t_data	data;
	int		width;
	int		height;
}	t_textures;

typedef struct s_sprite
{
	float		center_x;
	float		center_y;
	t_plane		plane;
	t_vector	v_norm;
}	t_sprite;

typedef struct s_sprites
{
	t_sprite	*sprite;
	int			num_sprite;
}	t_sprites;

typedef struct s_struct
{
	t_vars		vars;
	t_data		data;
	t_settings	set;
	t_rays		rays;
	t_planes	plane;
	t_player	player;
	t_key		key;
	t_textures	*texture;
	t_sprites	sprites;
}	t_struct;

int				main(int ac, char **av);
void			init_struct_set(t_settings *set);
void			init_struct(t_struct *as);

void			parse_cub(t_struct *as, char *file_name);
void			get_settings(t_struct *as);
void			parsing(t_struct *as, int fd);
int				check_arg(t_settings *set, int i);
void			get_resolution(t_struct *as);
void			get_texture(t_struct *as);
void			get_color(t_struct *as);
int				ft_count(char const *s, char c);
unsigned int	get_rgb(unsigned int r, unsigned int g, unsigned int b);
void			map(t_struct *as, int fd);
void			setup_map(t_struct *as);
void			check_map(t_struct *as);
int				check_wall(t_struct *as, int i, int j);

void			free_split(char **tab, int i);
int				number_of_split(char **tab);
int				ft_isnumber(char *s);
void			ft_exit(t_struct *as, char *str);
int				destroy_win(t_struct *as);

void			player_spawn(t_struct *as);
int				key_press(int keycode, t_struct *as);
int				key_release(int keycode, t_struct *as);
int				player_move(t_struct *as);

void			ray(t_struct *as);
void			calc_ray(t_struct *as, float rh, float rv);
void			matrix(t_struct *as, int i);

void			init_plane(t_struct *as);
void			make_plane(t_struct *as);
void			fill_plane(t_struct *as, char wall, int i);
void			init_sprite(t_struct *as);
void			make_sprite(t_struct *as);

void			create_textures(t_struct *as);
int				draw(t_struct *as);
void			put_floor_and_ceiling(t_struct *as);
void			draw_wall(t_struct *as);
void			find_inter(t_struct *as);
void			find_t_wall(t_struct *as, int i, int j);
void			draw_sprite(t_struct *as);
void			find_t_sprite(t_struct *as, int i, int j);

int				my_mlx_px_get(t_struct *as, int x, int y, int wall);
void			my_mlx_px_put(t_struct *as, int x, int y, int color);

#endif
