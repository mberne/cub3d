#include "cub3d.h"

void	put_floor_and_ceiling(t_struct *as)
{
	int	i;
	int	j;

	i = 0;
	while (i < V_RES / 2)
	{
		j = 0;
		while (j < H_RES)
		{
			my_px_put(as, j, i, as->set.ceiling);
			j++;
		}
		i++;
	}
	while (i < V_RES)
	{
		j = 0;
		while (j < H_RES)
		{
			my_px_put(as, j, i, as->set.floor);
			j++;
		}
		i++;
	}
}

int	draw(t_struct *as)
{
	player_move(as);
	put_floor_and_ceiling(as);
	find_inter_wall(as);
	draw_wall(as);
	mlx_put_image_to_window(as->vars.mlx, as->vars.win, as->data.img, 0, 0);
	mlx_do_sync(as->vars.mlx);
	return (0);
}
