#include "cub3d.h"

void	my_mlx_px_put(t_struct *as, int x, int y, int color)
{
	char	*dst;

	dst = as->data.addr + (y * as->data.line_length + x
			*(as->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	find_wall(t_struct *as)
{
	int		i;
	int		j;
	float	t;
	float	tmp;
	int		target_plane;

	player_move(as);
	i = 0;
	while (i < as->rays.num_r)
	{
		j = 0;
		matrix(as, i);
		float	*newray = as->rays.new_ray;
		t = INFINITY;
		target_plane = 0;
		while (j < as->plane.num_plane)
		{
			t_plane	plane = as->plane.plane[j];
			tmp = -(plane.a * as->player.x
					+ plane.b * as->player.y
					+ plane.c * as->player.z
					+ plane.d)
				/ (plane.a * newray[0]
					+ plane.b * newray[1]
					+ plane.c * newray[2]);
			if (tmp > 0 && tmp < t)
			{
				int blockx = (int)(as->player.x + newray[0] * tmp);
				int blocky = (int)(as->player.y + newray[1] * tmp);
				if (blocky > 0
					&& blocky <= as->set.mapy
					&& blockx > 0 && blockx <= as->set.mapx
					&& (
					((plane.direction == 0 || plane.direction == 3) && as->set.map[blocky][blockx] == '1')
						|| (plane.direction == 1 && as->set.map[blocky][blockx - 1] == '1')
						|| (plane.direction == 2 && as->set.map[blocky - 1][blockx] == '1')))
				{
					t = tmp;
					target_plane = j;
				}
			}
			j++;
		}
		float z = as->player.z + newray[2] * t;
		if (z < 0)
			my_mlx_px_put(as, (i % as->set.res[0]),
				(i / as->set.res[0]), as->set.floor);
		else if (z > 0.2)
			my_mlx_px_put(as, (i % as->set.res[0]),
				(i / as->set.res[0]), as->set.ceiling);
		else if (z >= 0 && z <= 0.2)
		{
			if (target_plane % 4 == 0)
				my_mlx_px_put(as, (i % as->set.res[0]),
					(i / as->set.res[0]), 16777215);
			else if (target_plane % 4 == 1)
				my_mlx_px_put(as, (i % as->set.res[0]),
					(i / as->set.res[0]), 167772);
			else if (target_plane % 4 == 2)
				my_mlx_px_put(as, (i % as->set.res[0]),
					(i / as->set.res[0]), 1677);
			else if (target_plane % 4 == 3)
				my_mlx_px_put(as, (i % as->set.res[0]),
					(i / as->set.res[0]), 16);
		}
		i++;
	}
	mlx_put_image_to_window(as->vars.mlx, as->vars.win, as->data.img, 0, 0);
	return (0);
}
