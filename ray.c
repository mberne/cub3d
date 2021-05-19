#include "cub3d.h"

void	matrix(t_struct *as, int i)
{
	as->rays.inter[i].new_ray.x = as->rays.ray[i].x * cosf(as->player.rad)
		+ as->rays.ray[i].y * (-sinf(as->player.rad));
	as->rays.inter[i].new_ray.y = as->rays.ray[i].x * sinf(as->player.rad)
		+ as->rays.ray[i].y * cosf(as->player.rad);
	as->rays.inter[i].new_ray.z = as->rays.ray[i].z;
}

void	calc_ray(t_struct *as, float rh, float rv)
{
	int	i;
	int	j;

	i = 0;
	while (i < as->set.res[1])
	{
		j = 0;
		while (j < as->set.res[0])
		{
			as->rays.ray[as->rays.num_r].x = (j - as->set.res[0] * 0.5) * rh;
			as->rays.ray[as->rays.num_r].y = -1;
			as->rays.ray[as->rays.num_r].z = (as->set.res[1] * 0.5 - i) * rv;
			as->rays.num_r++;
			j++;
		}
		i++;
	}
}

void	ray(t_struct *as)
{
	float	d;
	float	rh;

	as->rays.ray = malloc(sizeof(t_vector)
			* ((as->set.res[0] + 1) * (as->set.res[1] + 1)));
	if (!as->rays.ray)
		ft_exit(as, "Error\nMalloc error\n");
	as->rays.num_r = 0;
	d = tan((FOV * M_PI / 180) / 2) * 2;
	rh = d / as->set.res[0];
	as->rays.rv = rh * as->set.res[1] / as->set.res[0];
	calc_ray(as, rh, as->rays.rv);
}
