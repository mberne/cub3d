/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:32:42 by mberne            #+#    #+#             */
/*   Updated: 2021/03/11 11:24:30 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_struct *as, int x, int y, int color)
{
	char	*dst;

	dst = as->data->addr + (y * as->data->line_length + x
			*(as->data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_exit(t_struct *as, char *str)
{
	printf("%s", str);
	free(as->set->file);
	free_split(as->set->tab, number_of_split(as->set->tab));
	free(as->set->line);
	free(as->set->no);
	free(as->set->so);
	free(as->set->we);
	free(as->set->ea);
	free(as->set->sprite);
	free_split(as->set->map, number_of_split(as->set->map));
	free(as->set);
	free(as->vars);
	free(as->data);
	exit(-1);
}

void	get_settings(t_struct *as)
{
	int		fd;
	int		ret;

	fd = open(as->set->file, O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &as->set->line);
		if (ret == -1)
			ft_exit(as, "Error\nAn error occured while reading file\n");
		if (*as->set->line)
		{
			as->set->tab = ft_split(as->set->line, ' ');
			parsing(as, fd);
			free(as->set->line);
			free_split(as->set->tab, number_of_split(as->set->tab));
			as->set->tab = 0;
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
	t_struct	as;
	int			i;
	int			j;

	(void)ac;
	as.set = malloc(sizeof(t_settings));
	as.vars = malloc(sizeof(t_vars));
	as.data = malloc(sizeof(t_data));
	if (!as.set || !as.vars || !as.data)
		ft_exit(&as, "Error\nMalloc error\n");
	init_struct(as.set);
	i = ft_strlen(av[1]);
	j = 0;
	if (i > 4 && av[1][--i] == 'b' && av[1][--i] == 'u' && av[1][--i] == 'c'
		&& av[1][--i] == '.')
	{
		as.set->file = ft_strdup(av[1]);
		if (!as.set->file)
			ft_exit(&as, "Error\nMalloc error\n");
	}
	else
		ft_exit(&as, "Error\nInvalid name of file\n");
	as.vars->mlx = mlx_init();
	get_settings(&as);
	if (as.set->res[0] == -1 || as.set->res[1] == -1 || !as.set->no
		|| !as.set->so || !as.set->we || !as.set->ea || !as.set->sprite
		|| as.set->floor == -1 || as.set->ceiling == -1 || !as.set->map)
		ft_exit(&as, "Error\nInvalid file\n");
	printf("file | %s\n", as.set->file);
	printf("res 1 | %d\n", as.set->res[0]);
	printf("res 2 | %d\n", as.set->res[1]);
	printf("NO | %s\n", as.set->no);
	printf("SO | %s\n", as.set->so);
	printf("WE | %s\n", as.set->we);
	printf("EA | %s\n", as.set->ea);
	printf("S | %s\n", as.set->sprite);
	printf("F | %d\n", as.set->floor);
	printf("C | %d\n", as.set->ceiling);
	while (as.set->map[j])
	{
		printf("|%s|\n", as.set->map[j]);
		j++;
	}
	printf("mapx | %d\n", as.set->mapx);
	printf("mapy | %d\n", as.set->mapy);
	printf("player position y | %d\n", as.set->pposition[0]);
	printf("player position x | %d\n", as.set->pposition[1]);
	printf("player orientation | %c\n", as.set->porientation);
	as.vars->win = mlx_new_window(as.vars->mlx, as.set->res[0], as.set->res[1], "Cub3D");
	as.data->img = mlx_new_image(as.vars->mlx, 920, 600);
	as.data->addr = mlx_get_data_addr(as.data->img, &as.data->bits_per_pixel,
			&as.data->line_length, &as.data->endian);
	// mlx_put_image_to_window(as.vars->mlx, as.vars->win, as.data->img, 0, 0);
	// mlx_loop(as.vars->mlx);
	// mlx_key_hook() || mlx_mouse_hook()
	// mlx_destroy_window(mlx, win);
}
