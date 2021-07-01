#include "cub3d.h"

int	cast_float_y(t_struct *as, int i, int j, float tmp)
{
	if (as->plane.plane[j].direction == 1 || as->plane.plane[j].direction == 3)
		return (as->player.y + as->rays.inter[i].new_ray.y * tmp);
	else
		return (roundf(as->player.y + as->rays.inter[i].new_ray.y * tmp));
}

int	cast_float_x(t_struct *as, int i, int j, float tmp)
{
	if (as->plane.plane[j].direction == 1 || as->plane.plane[j].direction == 3)
		return (roundf(as->player.x + as->rays.inter[i].new_ray.x * tmp));
	else
		return (as->player.x + as->rays.inter[i].new_ray.x * tmp);
}

void	find_t_wall(t_struct *as, int i, int j)
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
		x = cast_float_x(as, i, j, tmp);
		y = cast_float_y(as, i, j, tmp);
		if (y > 0 && y <= as->set.mapy && x > 0 && x <= as->set.mapx
			&& (((plane.direction == 0 || plane.direction == 3)
					&& as->set.map[y][x] == '1')
			|| (plane.direction == 1 && as->set.map[y][x - 1] == '1')
			|| (plane.direction == 2 && as->set.map[y - 1][x] == '1')))
		{
			as->rays.inter[i].t = tmp;
			as->rays.inter[i].target_plane = j % 4;
		}
	}
}

void	find_inter_wall(t_struct *as)
{
	int		i;
	int		j;

	i = 0;
	as->rays.inter = malloc(sizeof(t_intersection) * H_RES);
	if (!as->rays.inter)
		ft_exit(as, "Error\nMalloc error\n");
	while (i < H_RES)
	{
		matrix(as, i);
		j = 0;
		as->rays.inter[i].t = INFINITY;
		as->rays.inter[i].target_plane = -1;
		while (j < as->plane.num_plane)
		{
			find_t_wall(as, i, j);
			j++;
		}
		i++;
	}
}
