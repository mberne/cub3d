#include "cub3d.h"

int	key_press(int keycode, t_struct *as)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(as->vars.mlx, as->vars.win);
		ft_exit(as, "");
	}
	if (keycode == LEFT_ARROW)
		as->key.t_left = 1;
	if (keycode == RIGHT_ARROW)
		as->key.t_right = 1;
	if (keycode == W)
		as->key.front = 1;
	if (keycode == S)
		as->key.back = 1;
	if (keycode == A)
		as->key.left = 1;
	if (keycode == D)
		as->key.right = 1;
	return (0);
}

int	key_release(int keycode, t_struct *as)
{
	if (keycode == LEFT_ARROW)
		as->key.t_left = 0;
	if (keycode == RIGHT_ARROW)
		as->key.t_right = 0;
	if (keycode == W)
		as->key.front = 0;
	if (keycode == S)
		as->key.back = 0;
	if (keycode == A)
		as->key.left = 0;
	if (keycode == D)
		as->key.right = 0;
	return (0);
}

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

int	destroy_win(t_struct *as)
{
	mlx_destroy_window(as->vars.mlx, as->vars.win);
	ft_exit(as, "");
	return (0);
}
