#include "cub3d.h"

void	my_mlx_pixel_put(t_struct *as, int x, int y, int color)
{
	char	*dst;

	dst = as->data.addr + (y * as->data.line_length + x
			*(as->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	find_wall(t_struct *as)
{
	int	i;
	int	d;

	i = 0;
	while (as->ray.ray[i])
	{
		d = 0;
		while (d <= ?)
		{
			//as->ray.t[i] = - ((0 * 0 + 1 * 0 + 0 * 0 + d) / (0 * as->ray.ray[i][0] + 1 * as->ray.ray[i][1] + 0 * as->ray.ray[i][2]));
			d++;
		}
		i++;
	}
}

void	ray(t_struct *as)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	as->ray.d = tan(FOV / 2) * 2;
	as->ray.rh = as->ray.d / as->set.res[0];
	as->ray.rv = (as->ray.rh * as->set.res[1]) / as->set.res[0];
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
