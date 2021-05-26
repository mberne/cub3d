#include "cub3d.h"

void	ft_exit(t_struct *as, char *str)
{
	printf("%s", str);
	free(as->set.file);
	free_split(as->set.tab, number_of_split(as->set.tab));
	free(as->set.line);
	free(as->set.no);
	free(as->set.so);
	free(as->set.we);
	free(as->set.ea);
	free_split(as->set.map, number_of_split(as->set.map));
	// détruis tes images de textures connasse
	exit(-1);
}

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
	get_settings(as);
	if (!as->set.no || !as->set.so || !as->set.we || !as->set.ea
		|| as->set.floor == -1 || as->set.ceiling == -1 || !as->set.map)
		ft_exit(as, "Error\nInvalid file\n");
}

void	init_struct(t_struct *as)
{
	as->plane.num_plane = 0;
	as->plane.num_wall = 0;
	as->rays.num_r = 0;
	as->key.t_left = 0;
	as->key.t_right = 0;
	as->key.front = 0;
	as->key.back = 0;
	as->key.left = 0;
	as->key.right = 0;
}

void	init_struct_set(t_settings *set)
{
	set->file = 0;
	set->tab = 0;
	set->line = 0;
	set->no = 0;
	set->so = 0;
	set->we = 0;
	set->ea = 0;
	set->floor = -1;
	set->ceiling = -1;
	set->map = 0;
	set->mapx = 0;
	set->mapy = 0;
	set->pposition[0] = -1;
	set->pposition[1] = -1;
	set->porientation = 0;
}

int	main(int ac, char **av)
{
	t_struct	as;

	(void)ac;
	as.vars.mlx = mlx_init();
	if (!as.vars.mlx)
		ft_exit(&as, "Error\nMalloc error\n");
	init_struct_set(&as.set);
	parse_cub(&as, av[1]);
	init_struct(&as);
	player_spawn(&as);
	ray(&as);
	init_plane(&as);
	make_plane(&as);
	create_textures(&as);
	as.vars.win = mlx_new_window(as.vars.mlx, H_RES, V_RES, "Cub3D");
	as.data.img = mlx_new_image(as.vars.mlx, H_RES, V_RES);
	as.data.addr = mlx_get_data_addr(as.data.img, &as.data.bits_per_pixel,
			&as.data.line_length, &as.data.endian);
	if (!as.vars.win || !as.data.img || !as.data.addr)
		ft_exit(&as, "Error\nMalloc error\n");
	mlx_hook(as.vars.win, 2, 0L, key_press, &as.vars);
	mlx_hook(as.vars.win, 3, 0L, key_release, &as.vars);
	mlx_hook(as.vars.win, 17, 0L, destroy_win, &as.vars);
	mlx_loop_hook(as.vars.mlx, draw, &as);
	mlx_loop(as.vars.mlx);
}
