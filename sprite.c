#include "cub3d.h"

void	init_sprite(t_struct *as)
{
	int	i;
	int	j;

	i = 0;
	while (as->set.map[i])
	{
		j = 0;
		while (as->set.map[i][j])
		{
			if (as->set.map[i][j] == '2')
				as->sprites.num_sprite++;
			j++;
		}
		i++;
	}
	as->sprites.sprite = malloc(sizeof(t_sprite) * as->sprites.num_sprite);
	if (!as->sprites.sprite)
		ft_exit(as, "Error\nMalloc error\n");
}

void	make_sprite(t_struct *as)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	k = 0;
	while (i <= as->set.mapy)
	{
		j = 0;
		while (j <= as->set.mapx)
		{
			if (as->set.map[i][j] == '2')
			{
				as->sprites.sprite[k].center_x = j + 0.5;
				as->sprites.sprite[k].center_y = i + 0.5;
				k++;
			}
			j++;
		}
		i++;
	}
}

void	find_t_sprite(t_struct *as, int i, int j)
{
	t_plane		plane;
	t_vector	newray;
	float		tmp;
	float		size_vector;

	newray = as->rays.inter[i].new_ray;
	plane = as->sprites.sprite[j].plane;
	tmp = -(plane.a * as->player.x + plane.b * as->player.y + plane.d)
		/ (plane.a * newray.x + plane.b * newray.y);
	if (tmp > 0 && tmp < as->rays.inter[i].t)
	{
		as->rays.inter[i].t = tmp;
		size_vector = hypotf(plane.b, -plane.a);
		as->sprites.sprite[j].v_norm.x = plane.b / size_vector;
		as->sprites.sprite[j].v_norm.y = -plane.a / size_vector;
	}
}

void	draw_sprite(t_struct *as)
{
	int			i;
	int			j;
	t_sprite	sprite;

	i = 0;
	while (i <= as->set.res[0])
	{
		j = 0;
		while (j < as->sprites.num_sprite)
		{
			sprite.plane.a = sprite.center_x - as->player.x;
			sprite.plane.b = sprite.center_y - as->player.y;
			sprite.plane.d = -(sprite.plane.a * sprite.center_x)
				- (sprite.plane.b * sprite.center_y);
			as->sprites.sprite[j] = sprite;
			find_t_sprite(as, i, j);
			j++;
		}
		i++;
	}
}
