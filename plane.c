#include "cub3d.h"
/*
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

void	make_plane(t_struct *as)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < as->set.mapy)
	{
		j = 0;
		while (j < as->set.mapx)
		{
			if (as->set.map[i][j] == '1')
			{
				as->plane.plane[k] = malloc(sizeof(int) * 4);
				if (!as->plane.plane[k])
					ft_exit(as, "Error\nMalloc error\n");
				as->plane.plane[k][0] = 0;
				as->plane.plane[k][1] = 1;
				as->plane.plane[k][2] = 0;
				as->plane.plane[k][3] = i;
				k++;
				as->plane.plane[k] = malloc(sizeof(int) * 4);
				if (!as->plane.plane[k])
					ft_exit(as, "Error\nMalloc error\n");
				as->plane.plane[k][0] = 1;
				as->plane.plane[k][1] = 0;
				as->plane.plane[k][2] = 0;
				as->plane.plane[k][3] = j + 1;
				k++;
				as->plane.plane[k] = malloc(sizeof(int) * 4);
				if (!as->plane.plane[k])
					ft_exit(as, "Error\nMalloc error\n");
				as->plane.plane[k][0] = 0;
				as->plane.plane[k][1] = 1;
				as->plane.plane[k][2] = 0;
				as->plane.plane[k][3] = i + 1;
				k++;
				as->plane.plane[k] = malloc(sizeof(int) * 4);
				if (!as->plane.plane[k])
					ft_exit(as, "Error\nMalloc error\n");
				as->plane.plane[k][0] = 1;
				as->plane.plane[k][1] = 0;
				as->plane.plane[k][2] = 0;
				as->plane.plane[k][3] = j;
				k++;
			}
			j++;
		}
		i++;
	}
	as->plane.num_plane = k;
}
*/