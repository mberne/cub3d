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
	float	z;

	as->plane.plane[0][0] = 0;
	as->plane.plane[0][1] = 1;
	as->plane.plane[0][2] = 0;
	as->plane.plane[0][3] = 4;
	as->plane.plane[1][0] = 0;
	as->plane.plane[1][1] = 1;
	as->plane.plane[1][2] = 0;
	as->plane.plane[1][3] = -4;
	as->plane.plane[2][0] = 1;
	as->plane.plane[2][1] = 0;
	as->plane.plane[2][2] = 0;
	as->plane.plane[2][3] = 4;
	as->plane.plane[3][0] = 1;
	as->plane.plane[3][1] = 0;
	as->plane.plane[3][2] = 0;
	as->plane.plane[3][3] = -4;
	as->plane.num_plane = 4;
	player_move(as);
	i = 0;
	while (i < as->ray.num_r)
	{
		matrix(as, i);
		j = 0;
		t = INFINITY;
		while (j < as->plane.num_plane)
		{
			tmp = - (as->plane.plane[j][0] * as->player.x
					+ as->plane.plane[j][1] * as->player.y
					+ as->plane.plane[j][2] * as->player.z
					+ as->plane.plane[j][3])
				/ (as->plane.plane[j][0] * as->ray.new_ray[0]
					+ as->plane.plane[j][1] * as->ray.new_ray[1]
					+ as->plane.plane[j][2] * as->ray.new_ray[2]);
			if (tmp > 0 && tmp < t)
				t = tmp;
			j++;
		}
		z = as->player.z + as->ray.new_ray[2] * t;
		if (z < 0)
			my_mlx_px_put(as, (i % as->set.res[0]), (i / as->set.res[0]), as->set.floor);
		else if (z > 1)
			my_mlx_px_put(as, (i % as->set.res[0]), (i / as->set.res[0]), as->set.ceiling);
		else if (z >= 0 && z <= 1)
			my_mlx_px_put(as, (i % as->set.res[0]), (i / as->set.res[0]), 16777215);
		i++;
	}
	mlx_put_image_to_window(as->vars.mlx, as->vars.win, as->data.img, 0, 0);
	return (0);
}
