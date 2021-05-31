#include "cub3d.h"

void	init_minimap(t_struct *as)
{
	as->minimap.width = H_RES / 3;
	as->minimap.height = V_RES / 4;
	as->minimap.w_box = as->minimap.width / as->set.mapx;
	as->minimap.h_box = as->minimap.height / as->set.mapy;
}

void	draw_player(t_struct *as)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	x = as->player.x * as->minimap.w_box - (as->minimap.w_box / 2) + 2;
	while (i < as->minimap.w_box - 4)
	{
		j = 0;
		y = as->player.y * as->minimap.h_box - (as->minimap.h_box / 2) + 2;
		while (j < as->minimap.h_box - 4)
		{
			my_px_put(as, x, y, 16711680);
			y++;
			j++;
		}
		x++;
		i++;
	}
}

void	square(t_struct *as, int color)
{
	int	i;
	int	j;
	int	x_px;
	int	y_px;

	i = 0;
	y_px = as->minimap.y_px;
	while (i < as->minimap.h_box)
	{
		j = 0;
		x_px = as->minimap.x_px;
		while (j < as->minimap.w_box)
		{
			my_px_put(as, x_px, y_px, color);
			x_px++;
			j++;
		}
		y_px++;
		i++;
	}
}

void	draw_minimap(t_struct *as)
{
	int	i;
	int	j;

	i = 0;
	as->minimap.y_px = 0;
	while (i <= as->set.mapy)
	{
		j = 0;
		as->minimap.x_px = 0;
		while (j <= as->set.mapx)
		{
			if (as->set.map[i][j] == '1')
				square(as, 16777215);
			else if (as->set.map[i][j] != ' ')
				square(as, 0);
			as->minimap.x_px += as->minimap.w_box;
			j++;
		}
		as->minimap.y_px += as->minimap.h_box;
		i++;
	}
	draw_player(as);
}
