#include "cub3d.h"

void	my_mlx_px_put(t_struct *as, int x, int y, int color)
{
	char	*dst;

	dst = as->data.addr + (y * as->data.line_length + x
			*(as->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	find_wall(t_struct *as)
{
	int		i;
	int		j;
	float	t;
	float	px[3];

	i = -1;
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
	while (++i < (as->set.res[0] * as->set.res[1]))
	{
		j = -1;
		while (++j < 4)
		{
			t = - (as->plane.plane[j][0] * 0 + as->plane.plane[j][1] * 0
					+ as->plane.plane[j][2] * 0 + as->plane.plane[j][3])
				/ (as->plane.plane[j][0] * as->ray.ray[i][0]
					+ as->plane.plane[j][1] * as->ray.ray[i][1]
					+ as->plane.plane[j][2] * as->ray.ray[i][2]);
			if (t > 0)
			{
				px[0] = 0 + as->ray.ray[i][0] * t;
				px[1] = 0 + as->ray.ray[i][1] * t;
				px[2] = 0 + as->ray.ray[i][2] * t;
				// if (px[2] > 1)
				// 	my_mlx_px_put(as, px[2], px[0], as->set.ceiling);
				// else if (px[2] < 0)
				// 	my_mlx_px_put(as, px[2], px[0], as->set.floor);
				// else
					my_mlx_px_put(as, px[2], px[0], 16777215);
			}
		}
	}
}

void	ray(t_struct *as)
{
	int		i;
	int		j;
	int		k;
	float	d;

	k = 0;
	d = tan(FOV / 2) * 2;
	as->ray.rh = d / as->set.res[0];
	as->ray.rv = as->ray.rh * as->set.res[1] / as->set.res[0];
	as->ray.ray = malloc(sizeof(float *)
			* ((as->set.res[0] + 1) * (as->set.res[1] + 1)));
	if (!as->ray.ray)
		ft_exit(as, "Error\nMalloc error\n");
	i = -1;
	while (++i <= as->set.res[0])
	{
		j = -1;
		while (++j <= as->set.res[1])
		{
			as->ray.ray[k] = malloc(sizeof(float) * 3);
			as->ray.ray[k][0] = (i - as->set.res[0] / 2) * as->ray.rh;
			as->ray.ray[k][1] = -1;
			as->ray.ray[k][2] = -(j - as->set.res[1] / 2) * as->ray.rv;
			k++;
		}
	}
}
