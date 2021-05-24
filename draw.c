#include "cub3d.h"

void	put_floor_and_ceiling(t_struct *as)
{
	int	i;
	int	j;

	i = 0;
	while (i < as->set.res[1] / 2)
	{
		j = 0;
		while (j < as->set.res[0])
		{
			my_mlx_px_put(as, j, i, as->set.ceiling);
			j++;
		}
		i++;
	}
	while (i < as->set.res[1])
	{
		j = 0;
		while (j < as->set.res[0])
		{
			my_mlx_px_put(as, j, i, as->set.floor);
			j++;
		}
		i++;
	}
}

int	draw(t_struct *as)
{
	put_floor_and_ceiling(as);
	player_move(as);
	find_inter(as);
	draw_wall(as);
	draw_sprite(as);
	mlx_put_image_to_window(as->vars.mlx, as->vars.win, as->data.img, 0, 0);
	mlx_do_sync(as->vars.mlx);
	as->player.z = 0.2;
	return (0);
}
