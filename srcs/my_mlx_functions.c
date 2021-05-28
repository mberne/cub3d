#include "cub3d.h"

void	my_px_put(t_struct *as, int x, int y, int color)
{
	char	*dst;

	dst = as->data.addr + (y * as->data.line_length
			+ x * as->texture->data.bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

int	my_px_get(t_struct *as, int x, int y, int wall)
{
	char	*dst;

	dst = as->texture[wall].data.addr + (y * as->texture[wall].data.line_length
			+ x * as->texture->data.bits_per_pixel / 8);
	return (*(int *)dst);
}
