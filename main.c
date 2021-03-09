/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:32:42 by mberne            #+#    #+#             */
/*   Updated: 2021/03/09 15:41:01 by mberne           ###   ########lyon.fr   */
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

void	ft_exit(t_settings *set, char *str)
{
	printf("%s", str);
	if (set->file)
		free(set->file);
	if (set->tab)
		free_split(set->tab, number_of_split(set->tab));
	if (set->line)
		free(set->line);
	if (set->no)
		free(set->no);
	if (set->so)
		free(set->so);
	if (set->we)
		free(set->we);
	if (set->ea)
		free(set->ea);
	if (set->sprite)
		free(set->sprite);
	if (set->map)
		free_split(set->map, number_of_split(set->map));
	exit(-1);
}

void	get_settings(t_settings *set)
{
	int		fd;
	int		ret;

	fd = open(set->file, O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &set->line);
		if (ret == -1)
			ft_exit(set, "Error\nAn error occured while reading file\n");
		if (*set->line)
		{
			set->tab = ft_split(set->line, ' ');
			parsing(set, fd);
			free(set->line);
			free_split(set->tab, number_of_split(set->tab));
			set->tab = 0;
		}
	}
}

void	init_struct(t_settings *set)
{
	set->file = 0;
	set->tab = 0;
	set->line = 0;
	set->res[0] = -1;
	set->res[1] = -1;
	set->no = 0;
	set->so = 0;
	set->we = 0;
	set->ea = 0;
	set->sprite = 0;
	set->floor = -1;
	set->ceiling = -1;
	set->map = 0;
	set->mapx = 0;
	set->mapy = 0;
	set->pposition[0] = -1;
	set->pposition[1] = -1;
	set->porientation = 0;
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
	{
		set.file = ft_strdup(av[1]);
		if (!set.file)
			ft_exit(&set, "Error\nMalloc error\n");
	}
	else
		ft_exit(&set, "Error\nInvalid name of file\n");
	get_settings(&set);
	if (set.res[0] == -1 || set.res[1] == -1 || !set.no || !set.so || !set.we
		|| !set.ea || !set.sprite || set.floor == -1 || set.ceiling == -1
		|| !set.map)
		ft_exit(&set, "Error\nInvalid file\n");
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
	printf("player position y | %d\n", set.pposition[0]);
	printf("player position x | %d\n", set.pposition[1]);
	printf("player orientation | %c\n", set.porientation);
}
