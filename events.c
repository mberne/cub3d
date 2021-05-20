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
	if (keycode == SPACE)
		as->key.space = 1;
	if (keycode == CROUCH)
		as->key.crouch = 1;
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
	if (keycode == SPACE)
		as->key.space = 0;
	if (keycode == CROUCH)
		as->key.crouch = 0;
	return (0);
}

int	player_move(t_struct *as)
{
	if (as->key.t_left)
		as->player.rad = as->player.rad - M_PI * 0.0075;
	if (as->key.t_right)
		as->player.rad = as->player.rad + M_PI * 0.0075;
	if (as->key.front)
	{
		as->player.x = as->player.x + sinf(as->player.rad) * 0.03;
		as->player.y = as->player.y - cosf(as->player.rad) * 0.03;
	}
	if (as->key.back)
	{
		as->player.x = as->player.x - sinf(as->player.rad) * 0.03;
		as->player.y = as->player.y + cosf(as->player.rad) * 0.03;
	}
	if (as->key.left)
	{
		as->player.x = as->player.x - cosf(as->player.rad) * 0.03;
		as->player.y = as->player.y - sinf(as->player.rad) * 0.03;
	}
	if (as->key.right)
	{
		as->player.x = as->player.x + cosf(as->player.rad) * 0.03;
		as->player.y = as->player.y + sinf(as->player.rad) * 0.03;
	}
	if (as->key.space && as->player.z < 0.3)
		as->player.z += 0.1;
	if (as->key.crouch && as->player.z > 0.1)
		as->player.z -= 0.1;
	return (0);
}

int	destroy_win(t_struct *as)
{
	mlx_destroy_window(as->vars.mlx, as->vars.win);
	ft_exit(as, "");
	return (0);
}
