#include "cub3d.h"

void	my_mlx_px_put(t_struct *as, int x, int y, int color)
{
	char	*dst;

	dst = as->data.addr + (y * as->data.line_length + x
			*(as->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	find_t(t_struct *as, int i, int j)
{
	t_plane	plane;
	float	*newray;
	float	tmp;
	int		x;
	int		y;

	newray = as->rays.new_ray;
	plane = as->plane.plane[j];
	tmp = -(plane.a * as->player.x + plane.b * as->player.y + plane.d)
		/ (plane.a * newray[0] + plane.b * newray[1]);
	if (tmp > 0 && tmp < as->rays.inter[i].t)
	{
		x = (int)(as->player.x + newray[0] * tmp);
		y = (int)(as->player.y + newray[1] * tmp);
		if (y > 0 && y <= as->set.mapy && x > 0 && x <= as->set.mapx
			&& (((plane.direction == 0 || plane.direction == 3)
					&& as->set.map[y][x] == '1')
			|| (plane.direction == 1 && as->set.map[y][x - 1] == '1')
			|| (plane.direction == 2 && as->set.map[y - 1][x] == '1')))
		{
			as->rays.inter[i].t = tmp;
			as->rays.inter[i].target_plane = j;
		}
	}
}

void	find_inter(t_struct *as)
{
	int		i;
	int		j;

	i = 0;
	as->rays.inter = malloc(sizeof(t_intersection) * (as->set.res[0] + 1));
	if (!as->rays.inter)
		ft_exit(as, "Error\nMalloc error\n");
	while (i <= as->set.res[0])
	{
		matrix(as, i);
		j = 0;
		as->rays.inter[i].t = INFINITY;
		as->rays.inter[i].target_plane = -1;
		while (j < as->plane.num_plane)
		{
			find_t(as, i, j);
			j++;
		}
		i++;
	}
}

void	put_floor_and_ceiling(t_struct *as)
{
	int	i;
	int	j;
	int	half_res;

	i = 0;
	half_res = as->set.res[1] / 2;
	while (i < half_res)
	{
		j = 0;
		while (j < as->set.res[0])
		{
			my_mlx_px_put(as, j, i, as->set.ceiling);
			j++;
		}
		i++;
	}
	while (i < as->set.res[1])
	{
		j = 0;
		while (j < as->set.res[0])
		{
			my_mlx_px_put(as, j, i, as->set.floor);
			j++;
		}
		i++;
	}
}

int	find_wall(t_struct *as)
{
	int		res;
	int		i;
	float	z;
	int		pixel;

	player_move(as);
	find_inter(as);
	put_floor_and_ceiling(as);
	res = as->set.res[0];
	i = 0;
	while (i < as->rays.num_r)
	{
		pixel = i % as->set.res[0];
		z = as->player.z + as->rays.ray[i].z * as->rays.inter[pixel].t;
		if (z >= 0 && z <= 0.2)
		{
			if (as->rays.inter[pixel].target_plane % 4 == 0)
				my_mlx_px_put(as, (i % res), (i / res), 16777215);
			else if (as->rays.inter[pixel].target_plane % 4 == 1)
				my_mlx_px_put(as, (i % res), (i / res), 167772);
			else if (as->rays.inter[pixel].target_plane % 4 == 2)
				my_mlx_px_put(as, (i % res), (i / res), 1677);
			else if (as->rays.inter[pixel].target_plane % 4 == 3)
				my_mlx_px_put(as, (i % res), (i / res), 16);
		}
		i++;
	}	
	mlx_put_image_to_window(as->vars.mlx, as->vars.win, as->data.img, 0, 0);
	return (0);
}