#include "cub3d.h"

int	key_events(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		mlx_destroy_window(vars->mlx, vars->win);
	/*
	if (keycode == LEFT_ARROW)
		// camera left rotate
	if (keycode == RIGHT_ARROW)
		// camera right rotate
	if (keycode == W)
		// déplacement perso' devant
	if (keycode == S)
		// déplacement perso' derriere
	if (keycode == A)
		// déplacement perso' gauche
	if (keycode == D)
		// déplacement perso' droite
	*/
	return (0);
}

int	destroy_win(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}
