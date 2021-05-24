#include "cub3d.h"

void	find_t(t_struct *as, int i, int j)
{
	t_plane		plane;
	t_vector	newray;
	float		tmp;
	int			x;
	int			y;

	newray = as->rays.inter[i].new_ray;
	plane = as->plane.plane[j];
	tmp = -(plane.a * as->player.x + plane.b * as->player.y + plane.d)
		/ (plane.a * newray.x + plane.b * newray.y);
	if (tmp > 0 && tmp < as->rays.inter[i].t)
	{
		if (plane.direction == 1 || plane.direction == 3)
		{
			x = roundf(as->player.x + newray.x * tmp);
			y = as->player.y + newray.y * tmp;
		}	
		else
		{
			x = as->player.x + newray.x * tmp;
			y = roundf(as->player.y + newray.y * tmp);
		}
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

void	draw_wall(t_struct *as)
{
	int			res;
	int			i;
	t_vector	inter;
	t_vector	ratio;
	int			px;
	int			t_x;
	int			t_y;

	res = as->set.res[0];
	i = 0;
	while (i < as->rays.num_r)
	{
		px = i % as->set.res[0];
		inter.x = as->player.x + as->rays.inter[px].new_ray.x * as->rays.inter[px].t;
		inter.y = as->player.y + as->rays.inter[px].new_ray.y * as->rays.inter[px].t;
		inter.z = as->player.z + (as->rays.inter[px].new_ray.z - (as->rays.rv * (i / as->set.res[0]))) * as->rays.inter[px].t;
		ratio.x = inter.x - (int)inter.x;
		ratio.y = inter.y - (int)inter.y;
		ratio.z = 1 - (inter.z - (int)inter.z);
		if (inter.z >= 0 && inter.z <= 0.4)
		{
			if (as->rays.inter[px].target_plane % 4 == 0)
			{
				t_x = ratio.x * as->texture[0].width;
				t_y = ratio.z * as->texture[0].height;
				my_mlx_px_put(as, (i % res), (i / res), my_mlx_px_get(as, t_x, t_y, 0));
			}
			else if (as->rays.inter[px].target_plane % 4 == 1)
			{
				t_x = ratio.y * as->texture[1].width;
				t_y = ratio.z * as->texture[1].height;
				my_mlx_px_put(as, (i % res), (i / res), my_mlx_px_get(as, t_x, t_y, 1));
			}
			else if (as->rays.inter[px].target_plane % 4 == 2)
			{
				t_x = ratio.x * as->texture[2].width;
				t_y = ratio.z * as->texture[2].height;
				my_mlx_px_put(as, (i % res), (i / res), my_mlx_px_get(as, t_x, t_y, 2));
			}
			else if (as->rays.inter[px].target_plane % 4 == 3)
			{
				t_x = ratio.y * as->texture[3].width;
				t_y = ratio.z * as->texture[3].height;
				my_mlx_px_put(as, (i % res), (i / res), my_mlx_px_get(as, t_x, t_y, 3));
			}
		}
		i++;
	}
}
