#include "cub3d.h"

void	init_plane(t_struct *as)
{
	int	i;
	int	j;

	i = 0;
	as->plane.num_wall = 0;
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

void	fill_plane(t_struct *as, char wall, int i)
{
	t_plane	plane;

	if (wall == 'N' || wall == 'S')
	{
		plane.a = 0;
		plane.b = 1;
	}
	else
	{
		plane.a = 1;
		plane.b = 0;
	}
	plane.c = 0;
	if (wall == 'N')
	{
		plane.direction = 0;
		plane.d = -i;
	}
	else if (wall == 'E')
	{
		plane.direction = 1;
		plane.d = -(i + 1);
	}
	else if (wall == 'S')
	{
		plane.direction = 2;
		plane.d = -(i + 1);
	}
	else if (wall == 'W')
	{
		plane.direction = 3;
		plane.d = -i;
	}
	as->plane.plane[as->plane.num_plane] = plane;
	as->plane.num_plane++;
}

void	make_plane(t_struct *as)
{
	int	i;
	int	j;

	i = 0;
	as->plane.num_plane = 0;
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
