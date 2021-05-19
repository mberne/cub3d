#include "cub3d.h"

void	my_mlx_px_put(t_struct *as, int x, int y, int color)
{
	char	*dst;

	dst = as->data.addr + (y * as->data.line_length + x * 4);
	*(unsigned int *)dst = color;
}

int	my_mlx_px_get(t_struct *as, int x, int y, int wall)
{
	char	*dst;

	dst = as->texture[wall].data.addr + (y * as->texture[wall].data.line_length
			+ x * 4);
	return (*(int *)dst);
}
