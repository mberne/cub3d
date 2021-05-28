#include "cub3d.h"

void	create_textures(t_struct *as)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		as->texture[i].data.img = mlx_xpm_file_to_image(as->vars.mlx,
				as->set.text[i], &as->texture[i].width, &as->texture[i].height);
		if (!as->texture[i].data.img)
			ft_exit(as, "Error\nAn error occured while using mlx\n");
		as->texture[i].data.addr = mlx_get_data_addr(as->texture[i].data.img,
				&as->texture[i].data.bits_per_pixel,
				&as->texture[i].data.line_length, &as->texture[i].data.endian);
		if (!as->texture[i].data.addr)
			ft_exit(as, "Error\nAn error occured while using mlx\n");
		i++;
	}
}
