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
	int		k;
	int		l;
	int		index;
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
	l = 0;
	i = 0;
	while (i < as->set.res[1])
	{
		j = 0;
		while (j < as->set.res[0])
		{
			matrix(as, l);
			k = 0;
			t = INFINITY;
			while (k < as->plane.num_plane)
			{
				tmp = - (as->plane.plane[k][0] * as->player.x
						+ as->plane.plane[k][1] * as->player.y
						+ as->plane.plane[k][2] * as->player.z
						+ as->plane.plane[k][3])
					/ (as->plane.plane[k][0] * as->ray.new_ray[0]
						+ as->plane.plane[k][1] * as->ray.new_ray[1]
						+ as->plane.plane[k][2] * as->ray.new_ray[2]);
				if (tmp > 0 && tmp < t)
				{
					t = tmp;
					index = k;
				}
				k++;
			}
			z = as->player.z + as->ray.new_ray[2] * -t;
			if (z < 0)
				my_mlx_px_put(as, j, i, as->set.floor);
			else if (z > 1)
				my_mlx_px_put(as, j, i, as->set.ceiling);
			else if (z >= 0 && z <= 1)
			{
				if (index == 0)
					my_mlx_px_put(as, j, i, 16777215);
				else if (index == 1)
					my_mlx_px_put(as, j, i, 167772);
				else if (index == 2)
					my_mlx_px_put(as, j, i, 1677);
				else if (index == 3)
					my_mlx_px_put(as, j, i, 16);
			}
			j++;
			l++;
		}
		i++;
	}
	mlx_put_image_to_window(as->vars.mlx, as->vars.win, as->data.img, 0, 0);
	return (0);
}
