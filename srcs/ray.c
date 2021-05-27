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
	while (i < V_RES)
	{
		j = 0;
		while (j < H_RES)
		{
			as->rays.ray[as->rays.num_r].x = (j - H_RES * 0.5) * rh;
			as->rays.ray[as->rays.num_r].y = -1;
			as->rays.ray[as->rays.num_r].z = (V_RES * 0.5 - i) * rv;
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
			* ((H_RES + 1) * (V_RES + 1)));
	if (!as->rays.ray)
		ft_exit(as, "Error\nMalloc error\n");
	d = tan((FOV * M_PI / 180) / 2) * 2;
	rh = d / H_RES;
	as->rays.rv = rh * V_RES / H_RES;
	calc_ray(as, rh, as->rays.rv);
}
