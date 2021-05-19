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
	free(as->set.sprite);
	free_split(as->set.map, number_of_split(as->set.map));
	// détruis tes images de textures conasse
	exit(-1);
}

void	get_settings(t_struct *as)
{
	int		fd;
	int		ret;

	fd = open(as->set.file, O_RDONLY);
	if (fd == -1)
		ft_exit(as, "Error\nFile failed to open\n");
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &as->set.line);
		if (ret == -1)
			ft_exit(as, "Error\nAn error occured while reading file\n");
		if (*as->set.line)
		{
			as->set.tab = ft_split(as->set.line, ' ');
			parsing(as, fd);
			free(as->set.line);
			free_split(as->set.tab, number_of_split(as->set.tab));
			as->set.tab = 0;
		}
	}
	if (close(fd) == -1)
		ft_exit(as, "Error\nFile failed to close\n");
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
	if (as->set.res[0] == -1 || as->set.res[1] == -1 || !as->set.no
		|| !as->set.so || !as->set.we || !as->set.ea || !as->set.sprite
		|| as->set.floor == -1 || as->set.ceiling == -1 || !as->set.map)
		ft_exit(as, "Error\nInvalid file\n");
}

void	init_struct(t_settings *set)
{
	set->file = 0;
	set->tab = 0;
	set->line = 0;
	set->res[0] = -1;
	set->res[1] = -1;
	set->no = 0;
	set->so = 0;
	set->we = 0;
	set->ea = 0;
	set->sprite = 0;
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
	init_struct(&as.set);
	parse_cub(&as, av[1]);
	player_spawn(&as);
	ray(&as);
	init_plane(&as);
	make_plane(&as);
	create_textures(&as);
	as.vars.win = mlx_new_window(as.vars.mlx, as.set.res[0], as.set.res[1],
			"Cub3D");
	as.data.img = mlx_new_image(as.vars.mlx, as.set.res[0], as.set.res[1]);
	as.data.addr = mlx_get_data_addr(as.data.img, &as.data.bits_per_pixel,
			&as.data.line_length, &as.data.endian);
	// protection adresse et image bonjour
	mlx_hook(as.vars.win, 2, 1L << 0, key_press, &as.vars);
	mlx_hook(as.vars.win, 3, 1L << 1, key_release, &as.vars);
	mlx_hook(as.vars.win, 17, 1L << 2, destroy_win, &as.vars);
	find_wall(&as);
	mlx_loop_hook(as.vars.mlx, find_wall, &as);
	mlx_loop(as.vars.mlx);
}
