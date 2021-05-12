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
	int		plane;

	player_move(as);
	i = 0;
	while (i < as->ray.num_r)
	{
		matrix(as, i);
		j = 0;
		t = INFINITY;
		plane = 0;
		while (j < as->plane.num_plane)
		{
			tmp = - (as->plane.plane[j][0] * as->player.x
					+ as->plane.plane[j][1] * as->player.y
					+ as->plane.plane[j][2] * as->player.z
					+ as->plane.plane[j][3])
				/ (as->plane.plane[j][0] * as->ray.new_ray[0]
					+ as->plane.plane[j][1] * as->ray.new_ray[1]
					+ as->plane.plane[j][2] * as->ray.new_ray[2]);
			as->plane.inter[0] = as->player.x + as->ray.new_ray[0] * tmp;
			as->plane.inter[1] = as->player.y + as->ray.new_ray[1] * tmp;
			if (tmp > 0 && as->plane.inter[1] > 0
				&& as->plane.inter[1] < as->set.mapy
				&& as->plane.inter[0] > 0 && as->plane.inter[0] < as->set.mapx
				&& (((j % 4 == 0 || j % 4 == 3)
						&& as->set.map[(int)(as->plane.inter[1])]
					[(int)(as->plane.inter[0])] == '1')
					|| (j % 4 == 1 && as->set.map[(int)(as->plane.inter[1])]
					[(int)(as->plane.inter[0]) - 1] == '1')
					|| (j % 4 == 2 && as->set.map[(int)(as->plane.inter[1]) - 1]
					[(int)(as->plane.inter[0])] == '1')))
			{
				if (tmp < t)
				{
					t = tmp;
					plane = j;
				}
			}
			j++;
		}
		as->plane.inter[0] = as->player.x + as->ray.new_ray[0] * t;
		as->plane.inter[1] = as->player.y + as->ray.new_ray[1] * t;
		as->plane.inter[2] = as->player.z + as->ray.new_ray[2] * t;
		if (as->plane.inter[2] < 0)
			my_mlx_px_put(as, (i % as->set.res[0]), (i / as->set.res[0]), as->set.floor);
		else if (as->plane.inter[2] > 0.2)
			my_mlx_px_put(as, (i % as->set.res[0]), (i / as->set.res[0]), as->set.ceiling);
		else if (as->plane.inter[2] >= 0 && as->plane.inter[2] <= 0.2)
		{
			if (plane % 4 == 0)
				my_mlx_px_put(as, (i % as->set.res[0]), (i / as->set.res[0]), 16777215);
			else if (plane % 4 == 1)
				my_mlx_px_put(as, (i % as->set.res[0]), (i / as->set.res[0]), 167772);
			else if (plane % 4 == 2)
				my_mlx_px_put(as, (i % as->set.res[0]), (i / as->set.res[0]), 1677);
			else if (plane % 4 == 3)
				my_mlx_px_put(as, (i % as->set.res[0]), (i / as->set.res[0]), 16);
		}
		i++;
	}
	mlx_put_image_to_window(as->vars.mlx, as->vars.win, as->data.img, 0, 0);
	return (0);
}
