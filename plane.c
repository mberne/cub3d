#include "cub3d.h"

void	init_plane(t_struct *as)
{
	int	i;
	int	j;

	i = 0;
	while (as->set.map[i])
	{
		j = 0;
		while (as->set.map[i][j])
		{
			if (as->set.map[i][j] == '1')
				as->plane.num_wall++;
			j++;
		}
		i++;
	}
	as->plane.plane = malloc(sizeof(t_plane) * (as->plane.num_wall * 4));
	if (!as->plane.plane)
		ft_exit(as, "Error\nMalloc error\n");
}

void	fill_plane_d(t_struct *as, char wall, int i)
{
	if (wall == 'N')
	{
		as->plane.plane[as->plane.num_plane].direction = 0;
		as->plane.plane[as->plane.num_plane].d = -i;
	}
	else if (wall == 'E')
	{
		as->plane.plane[as->plane.num_plane].direction = 1;
		as->plane.plane[as->plane.num_plane].d = -(i + 1);
	}
	else if (wall == 'S')
	{
		as->plane.plane[as->plane.num_plane].direction = 2;
		as->plane.plane[as->plane.num_plane].d = -(i + 1);
	}
	else
	{
		as->plane.plane[as->plane.num_plane].direction = 3;
		as->plane.plane[as->plane.num_plane].d = -i;
	}
}

void	fill_plane(t_struct *as, char wall, int i)
{
	if (wall == 'N' || wall == 'S')
	{
		as->plane.plane[as->plane.num_plane].a = 0;
		as->plane.plane[as->plane.num_plane].b = 1;
	}
	else
	{
		as->plane.plane[as->plane.num_plane].a = 1;
		as->plane.plane[as->plane.num_plane].b = 0;
	}
	as->plane.plane[as->plane.num_plane].c = 0;
	fill_plane_d(as, wall, i);
	as->plane.num_plane++;
}

void	make_plane(t_struct *as)
{
	int	i;
	int	j;

	i = 0;
	while (i <= as->set.mapy)
	{
		j = 0;
		while (j <= as->set.mapx)
		{
			if (as->set.map[i][j] == '1')
			{
				fill_plane(as, 'N', i);
				fill_plane(as, 'E', j);
				fill_plane(as, 'S', i);
				fill_plane(as, 'W', j);
			}
			j++;
		}
		i++;
	}
}
