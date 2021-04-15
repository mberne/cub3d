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
	// free as->ray.ray
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
	int			i;

	(void)ac;
	init_struct(&as.set);
	i = ft_strlen(av[1]);
	if (i > 4 && av[1][--i] == 'b' && av[1][--i] == 'u' && av[1][--i] == 'c'
		&& av[1][--i] == '.')
	{
		as.set.file = ft_strdup(av[1]);
		if (!as.set.file)
			ft_exit(&as, "Error\nMalloc error\n");
	}
	else
		ft_exit(&as, "Error\nInvalid name of file\n");
	as.vars.mlx = mlx_init();
	get_settings(&as);
	if (as.set.res[0] == -1 || as.set.res[1] == -1 || !as.set.no
		|| !as.set.so || !as.set.we || !as.set.ea || !as.set.sprite
		|| as.set.floor == -1 || as.set.ceiling == -1 || !as.set.map)
		ft_exit(&as, "Error\nInvalid file\n");
	as.vars.win = mlx_new_window(as.vars.mlx, as.set.res[0], as.set.res[1],
			"Cub3D");
	as.data.img = mlx_new_image(as.vars.mlx, as.set.res[0], as.set.res[1]);
	as.data.addr = mlx_get_data_addr(as.data.img, &as.data.bits_per_pixel,
			&as.data.line_length, &as.data.endian);
	mlx_hook(as.vars.win, 2, 1L << 0, key_events, &as.vars);
	mlx_hook(as.vars.win, 17, 1L << 2, destroy_win, &as.vars);
	player_spawn(&as);
	ray(&as);
	find_wall(&as);
	mlx_loop_hook(as.vars.mlx, find_wall, &as);
	mlx_loop(as.vars.mlx);
}
