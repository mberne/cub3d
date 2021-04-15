#include "cub3d.h"

void	matrix(t_struct *as, int i)
{
	as->ray.new_ray[0] = as->ray.ray[i][0] * cosf(as->player.rad)
		+ as->ray.ray[i][1] * (-sinf(as->player.rad));
	as->ray.new_ray[1] = as->ray.ray[i][0] * sinf(as->player.rad)
		+ as->ray.ray[i][1] * cosf(as->player.rad);
	as->ray.new_ray[2] = as->ray.ray[i][2];
}

void	ray(t_struct *as)
{
	int		i;
	int		j;
	float	d;

	as->ray.num_r = 0;
	d = tan((FOV * M_PI / 180) / 2) * 2;
	as->ray.rh = d / as->set.res[0];
	as->ray.rv = as->ray.rh * as->set.res[1] / as->set.res[0];
	as->ray.ray = malloc(sizeof(float *)
			* ((as->set.res[0] + 1) * (as->set.res[1] + 1)));
	if (!as->ray.ray)
		ft_exit(as, "Error\nMalloc error\n");
	i = -1;
	while (++i < as->set.res[1])
	{
		j = -1;
		while (++j < as->set.res[0])
		{
			as->ray.ray[as->ray.num_r] = malloc(sizeof(float) * 3);
			as->ray.ray[as->ray.num_r][0] = (j - as->set.res[0] * 0.5)
				* as->ray.rh;
			as->ray.ray[as->ray.num_r][1] = -1;
			as->ray.ray[as->ray.num_r][2] = (as->set.res[1] * 0.5 - i)
				* as->ray.rv;
			as->ray.num_r++;
		}
	}
}
