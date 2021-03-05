/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:32:42 by mberne            #+#    #+#             */
/*   Updated: 2021/03/05 16:00:17 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	affiche_un_carre_stp(t_data *img)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (x < 100)
	{
		my_mlx_pixel_put(img, x, y, 0x00FF0000);
		y = 0;
		while (y < 100)
		{
			my_mlx_pixel_put(img, x, y, 0x00FF0000);
			y++;
		}
		x++;
	}
}
*/
/*
	void	*mlx;
	void	*win;
	t_data	img;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "Cub3D");
	img.img = mlx_new_image(mlx, 920, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	affiche_un_carre_stp(&img);
	mlx_loop(mlx);
	//mlx_key_hook() || mlx_mouse_hook()
	//mlx_destroy_window(mlx, win);
*/

void	init_struct(t_settings *set)
{
	set->file = 0;
	set->split = 0;
	set->res[0] = 0;
	set->res[1] = 0;
	set->get_res = 0;
	set->no = 0;
	set->so = 0;
	set->we = 0;
	set->ea = 0;
	set->sprite = 0;
	set->floor = 0;
	set->get_floor = 0;
	set->ceiling = 0;
	set->get_ceiling = 0;
	set->map = 0;
	set->mapx = 0;
	set->mapy = 0;
}

int	main(int ac, char **av)
{
	t_settings	set;
	int			i;
	int			j;

	(void)ac;
	init_struct(&set);
	i = ft_strlen(av[1]);
	j = 0;
	if (i > 4 && av[1][--i] == 'b' && av[1][--i] == 'u' && av[1][--i] == 'c'
		&& av[1][--i] == '.')
		set.file = av[1];
	else
	{
		printf("Error\nInvalid name of file\n");
		exit(-1);
	}
	get_settings(&set);
	printf("file | %s\n", set.file);
	printf("res 1 | %d\n", set.res[0]);
	printf("res 2 | %d\n", set.res[1]);
	printf("NO | %s\n", set.no);
	printf("SO | %s\n", set.so);
	printf("WE | %s\n", set.we);
	printf("EA | %s\n", set.ea);
	printf("S | %s\n", set.sprite);
	printf("F | %d\n", set.floor);
	printf("C | %d\n", set.ceiling);
	while (set.map[j])
	{
		printf("|%s|\n", set.map[j]);
		j++;
	}
	printf("mapx | %d\n", set.mapx);
	printf("mapy | %d\n", set.mapy);
}
