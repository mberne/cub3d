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
	as->plane.plane = malloc(sizeof(int *) * (as->plane.num_wall * 4));
	if (!as->plane.plane)
		ft_exit(as, "Error\nMalloc error\n");
}

void	fill_plane(t_struct *as, char wall, int i)
{
	as->plane.plane[as->plane.num_plane] = malloc(sizeof(int) * 4);
	if (!as->plane.plane[as->plane.num_plane])
		ft_exit(as, "Error\nMalloc error\n");
	if (wall == 'N' || wall == 'S')
	{
		as->plane.plane[as->plane.num_plane][0] = 0;
		as->plane.plane[as->plane.num_plane][1] = 1;
	}
	else
	{
		as->plane.plane[as->plane.num_plane][0] = 1;
		as->plane.plane[as->plane.num_plane][1] = 0;
	}
	as->plane.plane[as->plane.num_plane][2] = 0;
	if (wall == 'N')
		as->plane.plane[as->plane.num_plane][3] = -i;
	else if (wall == 'E')
		as->plane.plane[as->plane.num_plane][3] = -(i + 1);
	else if (wall == 'S')
		as->plane.plane[as->plane.num_plane][3] = -(i + 1);
	else if (wall == 'W')
		as->plane.plane[as->plane.num_plane][3] = -i;
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
