#include "cub3d.h"

void	parse_cub(t_struct *as, char *file_name)
{
	int	i;

	i = ft_strlen(file_name);
	if (i > 4 && !ft_strncmp(&file_name[i - 4], ".cub", i))
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
	ft_bzero(as, sizeof(t_struct));
	as->set.floor = -1;
	as->set.ceiling = -1;
	as->set.pposition[0] = -1;
	as->set.pposition[1] = -1;
}

void	before_drawing(t_struct *as, int ac, char **av)
{
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
	init_minimap(as);
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
