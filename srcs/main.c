#include "cub3d.h"

void	parse_cub(t_struct *as, char *file_name)
{
	int	i;

	i = ft_strlen(file_name);
	if (i > 4 && file_name[--i] == 'b' && file_name[--i] == 'u'
		&& file_name[--i] == 'c' && file_name[--i] == '.')
	{
		as->set.file = ft_strdup(file_name);
		if (!as->set.file)
			ft_exit(as, "Error\nMalloc error\n");
	}
	else
		ft_exit(as, "Error\nInvalid name of file\n");
	get_settings(as, 0, 1);
	if (!as->set.text[0] || !as->set.text[1] || !as->set.text[2]
		|| !as->set.text[3] || as->set.floor == -1 || as->set.ceiling == -1
		|| !as->set.map)
		ft_exit(as, "Error\nInvalid file\n");
}

void	init_struct(t_struct *as)
{
	int	i;

	i = 0;
	as->plane.num_plane = 0;
	as->plane.num_wall = 0;
	as->rays.num_r = 0;
	as->key.t_left = 0;
	as->key.t_right = 0;
	as->key.front = 0;
	as->key.back = 0;
	as->key.left = 0;
	as->key.right = 0;
	while (i < 4)
	{
		as->texture[i].data.img = 0;
		i++;
	}
	as->data.img = 0;
}

void	init_struct_set(t_struct *as)
{
	as->set.file = 0;
	as->set.tab = 0;
	as->set.line = 0;
	as->set.text[0] = 0;
	as->set.text[1] = 0;
	as->set.text[2] = 0;
	as->set.text[3] = 0;
	as->set.floor = -1;
	as->set.ceiling = -1;
	as->set.map = 0;
	as->set.mapx = 0;
	as->set.mapy = 0;
	as->set.pposition[0] = -1;
	as->set.pposition[1] = -1;
	as->set.porientation = 0;
}

void	before_drawing(t_struct *as, int ac, char **av)
{
	init_struct_set(as);
	init_struct(as);
	if (ac != 2)
		ft_exit(as, "Error\nInvalid number of argument\n");
	as->vars.mlx = mlx_init();
	if (!as->vars.mlx)
		ft_exit(as, "Error\nAn error occured while using mlx\n");
	parse_cub(as, av[1]);
	player_spawn(as);
	ray(as);
	init_plane(as);
	make_plane(as);
	create_textures(as);
}

int	main(int ac, char **av)
{
	t_struct	as;

	before_drawing(&as, ac, av);
	as.vars.win = mlx_new_window(as.vars.mlx, H_RES, V_RES, "Cub3D");
	if (!as.vars.win)
		ft_exit(&as, "Error\nAn error occured while using mlx\n");
	as.data.img = mlx_new_image(as.vars.mlx, H_RES, V_RES);
	if (!as.data.img)
		ft_exit(&as, "Error\nAn error occured while using mlx\n");
	as.data.addr = mlx_get_data_addr(as.data.img, &as.data.bits_per_pixel,
			&as.data.line_length, &as.data.endian);
	if (!as.data.addr)
		ft_exit(&as, "Error\nAn error occured while using mlx\n");
	mlx_hook(as.vars.win, 2, 0L, key_press, &as.vars);
	mlx_hook(as.vars.win, 3, 0L, key_release, &as.vars);
	mlx_hook(as.vars.win, 17, 0L, destroy_win, &as.vars);
	mlx_loop_hook(as.vars.mlx, draw, &as);
	mlx_loop(as.vars.mlx);
	return (0);
}
