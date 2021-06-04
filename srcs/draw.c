#include "cub3d.h"

void	put_texture(t_struct *as, int *px, t_vector ratio, int *t)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (as->rays.inter[px[0]].target_plane == i && i != 1)
		{
			t[0] = ratio.x * as->texture[i].width;
			t[1] = ratio.z * as->texture[i].height;
			if (t[0] < as->texture->height && t[1] < as->texture->width)
				my_px_put(as, (px[0]), (px[1]), my_px_get(as, t[0], t[1], i));
		}
	}
	i = 0;
	while (++i < 4)
	{
		if (as->rays.inter[px[0]].target_plane == i && i != 2)
		{
			t[0] = ratio.y * as->texture[i].width;
			t[1] = ratio.z * as->texture[i].height;
			if (t[0] < as->texture->height && t[1] < as->texture->width)
				my_px_put(as, (px[0]), (px[1]), my_px_get(as, t[0], t[1], i));
		}
	}
}

t_vector	calc_inter(t_struct *as, int *px)
{
	t_vector	inter;

	inter.x = as->player.x + as->rays.inter[px[0]].new_ray.x
		* as->rays.inter[px[0]].t;
	inter.y = as->player.y + as->rays.inter[px[0]].new_ray.y
		* as->rays.inter[px[0]].t;
	inter.z = as->player.z + (as->rays.inter[px[0]].new_ray.z
			- (as->rays.rv * (px[1]))) * as->rays.inter[px[0]].t;
	return (inter);
}

void	draw_wall(t_struct *as)
{
	int			i;
	t_vector	ratio;
	t_vector	inter;
	int			px[2];
	int			t[2];

	i = 0;
	while (i < as->rays.num_r)
	{
		px[0] = i % H_RES;
		px[1] = i / H_RES;
		inter = calc_inter(as, px);
		ratio.x = inter.x - (int)inter.x;
		ratio.y = inter.y - (int)inter.y;
		ratio.z = 1 - inter.z;
		if (inter.z <= 0)
			my_px_put(as, px[0], px[1], as->set.floor);
		else if (inter.z > 0 && inter.z < 1)
			put_texture(as, px, ratio, t);
		else if (inter.z >= 1)
			my_px_put(as, px[0], px[1], as->set.ceiling);
		i++;
	}
}

int	draw(t_struct *as)
{
	player_move(as);
	find_inter_wall(as);
	draw_wall(as);
	draw_minimap(as);
	mlx_put_image_to_window(as->vars.mlx, as->vars.win, as->data.img, 0, 0);
	mlx_do_sync(as->vars.mlx);
	free(as->rays.inter);
	return (0);
}
