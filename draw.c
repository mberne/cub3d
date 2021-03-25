#include "cub3d.h"

void	my_mlx_pixel_put(t_struct *as, int x, int y, int color)
{
	char	*dst;

	dst = as->data.addr + (y * as->data.line_length + x
			*(as->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// void	draw_minimap(t_struct *as)
// {
// 	int	x;
// 	int	y;

// 	y = -1;
// 	while (++y <= as->set.mapy)
// 	{
// 		x = -1;
// 		while (++x <= as->set.mapx)
// 		{
// 			if (as->set.map[y][x] == '1')
// 				draw_square(as, 0);
// 			else
// 				draw_square(as, 10000000);
// 		}
// 	}
// }

// void	square(t_struct *as)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	while (x <= 20)
// 	{
// 		y = 0;
// 		while (y <= 20)
// 		{
// 			my_mlx_pixel_put(as, x, y, 100000);
// 			y++;
// 		}
// 		x++;
// 	}
// }
