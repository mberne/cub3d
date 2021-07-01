#include "cub3d.h"

int	key_press(int keycode, t_struct *as)
{
	if (keycode == ESC)
		ft_exit(as, "Thanks for playing <3");
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
	if (keycode == F && !as->key.mouse)
	{
		as->key.mouse = 1;
		mlx_mouse_hide();
	}
	else if (keycode == F && as->key.mouse)
	{
		mlx_mouse_show();
		as->key.mouse = 0;
	}
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
	int	i;

	i = 0;
	printf("\n%s", str);
	if (as->vars.win)
		mlx_destroy_window(as->vars.mlx, as->vars.win);
	free(as->set.file);
	free_split(as->set.tab, number_of_split(as->set.tab));
	free(as->set.line);
	free(as->set.text[0]);
	free(as->set.text[1]);
	free(as->set.text[2]);
	free(as->set.text[3]);
	free_split(as->set.map, number_of_split(as->set.map));
	free(as->rays.ray);
	free(as->plane.plane);
	while (i < 4)
	{
		if (as->texture[i].data.img)
			mlx_destroy_image(as->vars.mlx, as->texture[i].data.img);
		i++;
	}
	if (as->data.img)
		mlx_destroy_image(as->vars.mlx, as->data.img);
	exit(-1);
}

int	destroy_win(t_struct *as)
{
	ft_exit(as, "Thanks for playing <3");
	return (0);
}
