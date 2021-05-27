#include "cub3d.h"

void	create_textures(t_struct *as)
{
	int	i;

	i = 0;
	as->texture = malloc(sizeof(t_textures) * 4);
	if (!as->texture)
		ft_exit(as, "Error\nMalloc error\n");
	as->texture[0].data.img = mlx_xpm_file_to_image(as->vars.mlx, as->set.no,
			&as->texture[0].width, &as->texture[0].height);
	as->texture[1].data.img = mlx_xpm_file_to_image(as->vars.mlx, as->set.ea,
			&as->texture[1].width, &as->texture[1].height);
	as->texture[2].data.img = mlx_xpm_file_to_image(as->vars.mlx, as->set.so,
			&as->texture[2].width, &as->texture[2].height);
	as->texture[3].data.img = mlx_xpm_file_to_image(as->vars.mlx, as->set.we,
			&as->texture[3].width, &as->texture[3].height);
	while (i < 4)
	{
		as->texture[i].data.addr = mlx_get_data_addr(as->texture[i].data.img,
				&as->texture[i].data.bits_per_pixel,
				&as->texture[i].data.line_length, &as->texture[i].data.endian);
		if (!as->texture[i].data.img || !as->texture[i].data.addr)
			ft_exit(as, "Error\nMalloc error\n");
		i++;
	}
}
