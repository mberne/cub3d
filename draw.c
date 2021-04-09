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
	float	t;
	float	tmp;

	as->plane.plane[0][0] = 0;
	as->plane.plane[0][1] = 1;
	as->plane.plane[0][2] = 0;
	as->plane.plane[0][3] = 2;
	as->plane.plane[1][0] = 0;
	as->plane.plane[1][1] = 1;
	as->plane.plane[1][2] = 0;
	as->plane.plane[1][3] = -2;
	as->plane.plane[2][0] = 1;
	as->plane.plane[2][1] = 0;
	as->plane.plane[2][2] = 0;
	as->plane.plane[2][3] = 2;
	as->plane.plane[3][0] = 1;
	as->plane.plane[3][1] = 0;
	as->plane.plane[3][2] = 0;
	as->plane.plane[3][3] = -2;
	k = 0;
	i = -1;
	matrix(as);
	while (++i < as->set.res[1])
	{
		j = -1;
		while (++j < as->set.res[0])
		{
			l = -1;
			t = INFINITY;
			while (++l < 4)
			{
				tmp = - (as->plane.plane[l][0] * as->player.x
						+ as->plane.plane[l][1] * as->player.y
						+ as->plane.plane[l][2] * as->player.z
						+ as->plane.plane[l][3])
					/ (as->plane.plane[l][0] * as->ray.ray[k][0]
						+ as->plane.plane[l][1] * as->ray.ray[k][1]
						+ as->plane.plane[l][2] * as->ray.ray[k][2]);
				if (tmp > 0 && tmp < t)
					t = tmp;
			}
			t = as->player.z + as->ray.ray[k][2] * -t;
			if (t < 0)
				my_mlx_px_put(as, j, i, as->set.floor);
			else if (t > 1)
				my_mlx_px_put(as, j, i, as->set.ceiling);
			else if (t >= 0 && t <= 1)
				my_mlx_px_put(as, j, i, 16777215);
			k++;
		}
	}
	mlx_put_image_to_window(as->vars.mlx, as->vars.win, as->data.img, 0, 0);
	return (0);
}
