#include "cub3d.h"

int	close_win(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}
