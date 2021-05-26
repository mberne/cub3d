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
	t_sprite	sprite;
	float		tmp;
	float		size_vector;

	newray = as->rays.inter[i].new_ray;
	plane = as->sprites.sprite[j].plane;
	tmp = -(plane.a * as->player.x + plane.b * as->player.y + plane.d)
		/ (plane.a * newray.x + plane.b * newray.y);
	if (tmp > 0 && tmp < as->rays.inter[i].t)
	{
		size_vector = hypotf(plane.b, -plane.a);
		sprite.v_norm.x = plane.b / size_vector;
		sprite.v_norm.y = -plane.a / size_vector;
		sprite.r = ((as->player.x + newray.x * tmp) - sprite.center_x)
			* sprite.v_norm.x + ((as->player.y + newray.y * tmp)
				- sprite.center_y) * sprite.v_norm.y + 0.5;
		if (sprite.r >= 0 && sprite.r < 1)
			as->rays.inter[i].t = tmp;
	}
}

void	find_inter_sprite(t_struct *as)
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

void	draw_sprite(t_struct *as)
{
	int			i;
	t_vector	inter;
	t_vector	ratio;
	int			px_x;
	int			px_y;
	int			t_x;
	int			t_y;

	i = 0;
	while (i < as->rays.num_r)
	{
		px_x = i % as->set.res[0];
		px_y = i / as->set.res[0];
		inter.z = as->player.z + (as->rays.inter[px_x].new_ray.z - (as->rays.rv * (px_y))) * as->rays.inter[px_x].t;
		ratio.z = 1 - (inter.z - (int)inter.z);
		if (inter.z >= 0 && inter.z <= 0.4)
		{
			t_x = as->sprites.sprite[px_x].r;
			t_y = ratio.z * as->texture[4].height;
			my_mlx_px_put(as, (px_x), (px_y), my_mlx_px_get(as, t_x, t_y, 4));
		}
		i++;
	}
}
