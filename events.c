#include "cub3d.h"

int	key_events(int keycode, t_struct *as)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(as->vars.mlx, as->vars.win);
		ft_exit(as, "");
	}
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

int	destroy_win(t_struct *as)
{
	mlx_destroy_window(as->vars.mlx, as->vars.win);
	ft_exit(as, "");
	return (0);
}
