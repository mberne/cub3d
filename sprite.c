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
	t_sprite	sprite;

	i = 0;
	k = 0;
	while (i <= as->set.mapy)
	{
		j = 0;
		while (j <= as->set.mapx)
		{
			if (as->set.map[i][j] == '2')
			{
				sprite.center_x = j + 0.5;
				sprite.center_y = i + 0.5;
				sprite.plane.a = sprite.center_x - as->player.x;
				sprite.plane.b = sprite.center_y - as->player.y;
				sprite.plane.d = -(sprite.plane.a * sprite.center_x)
					- (sprite.plane.b * sprite.center_y);
				as->sprites.sprite[k] = sprite;
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
	int			x;
	int			y;

	newray = as->rays.inter[i].new_ray;
	plane = as->sprites.sprite[j].plane;
	tmp = -(plane.a * as->player.x + plane.b * as->player.y + plane.d)
		/ (plane.a * newray.x + plane.b * newray.y);
	if (tmp > 0 && tmp < as->rays.inter[i].t)
	{
		as->sprites.sprite[j].v.x = as->sprites.sprite[j].plane.b;
		as->sprites.sprite[j].v.y = as->sprites.sprite[j].plane.a;
	}
}

void	draw_sprite(t_struct *as)
{
	int	i;
	int	j;

	i = 0;
	while (i <= as->set.res[0])
	{
		j = 0;
		as->rays.inter[i].t = INFINITY;
		while (j < as->sprites.num_sprite)
		{
			find_t_sprite(as, i, j);
			j++;
		}
		i++;
	}
}
