#include "cub3d.h"

int	key_events(int keycode, t_struct *as)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(as->vars.mlx, as->vars.win);
		ft_exit(as, "");
	}
	if (keycode == LEFT_ARROW)
		as->player.rad = as->player.rad + 0.01;
	if (keycode == RIGHT_ARROW)
		as->player.rad = as->player.rad - 0.01;
	if (keycode == W)
		as->player.y = as->player.y - 0.1;
	if (keycode == S)
		as->player.y = as->player.y + 0.1;
	if (keycode == A)
		as->player.x = as->player.x + 0.1;
	if (keycode == D)
		as->player.x = as->player.x - 0.1;
	return (0);
}

int	destroy_win(t_struct *as)
{
	mlx_destroy_window(as->vars.mlx, as->vars.win);
	ft_exit(as, "");
	return (0);
}
