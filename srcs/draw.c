#include "cub3d.h"

void	put_texture(t_struct *as, int *px, t_vector ratio, int *t)
{
	if (as->rays.inter[px[0]].target_plane == 0)
	{
		t[0] = ratio.x * as->texture[0].width;
		t[1] = ratio.z * as->texture[0].height;
		my_px_put(as, (px[0]), (px[1]), my_px_get(as, t[0], t[1], 0));
	}
	else if (as->rays.inter[px[0]].target_plane == 1)
	{
		t[0] = ratio.y * as->texture[1].width;
		t[1] = ratio.z * as->texture[1].height;
		my_px_put(as, (px[0]), (px[1]), my_px_get(as, t[0], t[1], 1));
	}
	else if (as->rays.inter[px[0]].target_plane == 2)
	{
		t[0] = ratio.x * as->texture[2].width;
		t[1] = ratio.z * as->texture[2].height;
		my_px_put(as, (px[0]), (px[1]), my_px_get(as, t[0], t[1], 2));
	}
	else if (as->rays.inter[px[0]].target_plane == 3)
	{
		t[0] = ratio.y * as->texture[3].width;
		t[1] = ratio.z * as->texture[3].height;
		my_px_put(as, (px[0]), (px[1]), my_px_get(as, t[0], t[1], 3));
	}
}

void	draw_wall(t_struct *as)
{
	int			i;
	t_vector	inter;
	t_vector	ratio;
	int			px[2];
	int			t[2];

	i = 0;
	while (i < as->rays.num_r)
	{
		px[0] = i % H_RES;
		px[1] = i / H_RES;
		inter.x = as->player.x + as->rays.inter[px[0]].new_ray.x
			* as->rays.inter[px[0]].t;
		inter.y = as->player.y + as->rays.inter[px[0]].new_ray.y
			* as->rays.inter[px[0]].t;
		inter.z = as->player.z + (as->rays.inter[px[0]].new_ray.z
				- (as->rays.rv * (px[1]))) * as->rays.inter[px[0]].t;
		ratio.x = inter.x - (int)inter.x;
		ratio.y = inter.y - (int)inter.y;
		ratio.z = 1 - (inter.z - (int)inter.z);
		if (inter.z >= 0 && inter.z <= 0.4)
			put_texture(as, px, ratio, t);
		i++;
	}
}

void	put_floor_and_ceiling(t_struct *as)
{
	int	i;
	int	j;

	i = 0;
	while (i < V_RES / 2)
	{
		j = 0;
		while (j < H_RES)
		{
			my_px_put(as, j, i, as->set.ceiling);
			j++;
		}
		i++;
	}
	while (i < V_RES)
	{
		j = 0;
		while (j < H_RES)
		{
			my_px_put(as, j, i, as->set.floor);
			j++;
		}
		i++;
	}
}

int	draw(t_struct *as)
{
	player_move(as);
	put_floor_and_ceiling(as);
	find_inter_wall(as);
	draw_wall(as);
	mlx_put_image_to_window(as->vars.mlx, as->vars.win, as->data.img, 0, 0);
	mlx_do_sync(as->vars.mlx);
	free(as->rays.inter);
	return (0);
}
