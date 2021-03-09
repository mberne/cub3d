/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:47:14 by mberne            #+#    #+#             */
/*   Updated: 2021/03/09 15:42:38 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = r * 256 * 256;
	j = g * 256;
	k = b;
	return (i + j + k);
}

void	get_color(t_settings *set)
{
	char			**rgb;
	unsigned int	color[3];

	rgb = ft_split(set->tab[1], ',');
	if (!rgb)
		ft_exit(set, "Error\nMalloc error\n");
	if (number_of_split(rgb) != 3 || !ft_isnumber(rgb[0])
		|| !ft_isnumber(rgb[1]) || !ft_isnumber(rgb[2])
		|| ft_count(set->tab[1], ',') != 2)
	{
		free_split(rgb, number_of_split(rgb));
		ft_exit(set, "Error\nInvalid color\n");
	}
	color[0] = ft_atoi(rgb[0]);
	color[1] = ft_atoi(rgb[1]);
	color[2] = ft_atoi(rgb[2]);
	free_split(rgb, number_of_split(rgb));
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
		ft_exit(set, "Error\nInvalid color\n");
	if (!ft_strncmp(set->tab[0], "F", 1) && set->floor == -1)
		set->floor = get_rgb(color[0], color[1], color[2]);
	else if (!ft_strncmp(set->tab[0], "C", 1) && set->ceiling == -1)
		set->ceiling = get_rgb(color[0], color[1], color[2]);
	else
		ft_exit(set, "Error\nInvalid color\n");
}

void	get_texture(t_settings *set)
{
	if (!ft_strncmp(set->tab[0], "NO", 2) && set->no == 0)
		set->no = ft_strdup(set->tab[1]);
	else if (!ft_strncmp(set->tab[0], "SO", 2) && set->so == 0)
		set->so = ft_strdup(set->tab[1]);
	else if (!ft_strncmp(set->tab[0], "WE", 2) && set->we == 0)
		set->we = ft_strdup(set->tab[1]);
	else if (!ft_strncmp(set->tab[0], "EA", 2) && set->ea == 0)
		set->ea = ft_strdup(set->tab[1]);
	else if (!ft_strncmp(set->tab[0], "S", 1)
		&& ft_strncmp(set->tab[0], "SO", 2) && set->sprite == 0)
		set->sprite = ft_strdup(set->tab[1]);
	else
		ft_exit(set, "Error\nInvalid textures\n");
}

void	get_resolution(t_settings *set)
{
	// mlx_get_screen_size()
	if (set->res[0] == -1 && set->res[1] == -1
		&& ft_isnumber(set->tab[1]) && ft_isnumber(set->tab[2]))
	{
		set->res[0] = ft_atoi(set->tab[1]);
		set->res[1] = ft_atoi(set->tab[2]);
		if (set->res[0] <= 0 || set->res[1] <= 0)
			ft_exit(set, "Error\nInvalid resolution\n");
	}
	else
		ft_exit(set, "Error\nInvalid resolution\n");
}

void	parsing(t_settings *set, int fd)
{
	if (!ft_strncmp(set->tab[0], "R", ft_strlen(set->tab[0]))
		&& check_arg(set, 3))
		get_resolution(set);
	else if ((!ft_strncmp(set->tab[0], "NO", ft_strlen(set->tab[0]))
			|| !ft_strncmp(set->tab[0], "SO", ft_strlen(set->tab[0]))
			|| !ft_strncmp(set->tab[0], "WE", ft_strlen(set->tab[0]))
			|| !ft_strncmp(set->tab[0], "EA", ft_strlen(set->tab[0]))
			|| !ft_strncmp(set->tab[0], "S", ft_strlen(set->tab[0])))
		&& check_arg(set, 2))
		get_texture(set);
	else if (check_arg(set, 2)
		&& (!ft_strncmp(set->tab[0], "F", ft_strlen(set->tab[0]))
			|| !ft_strncmp(set->tab[0], "C", ft_strlen(set->tab[0]))))
		get_color(set);
	else if (!ft_strncmp(set->tab[0], "1", 1))
	{
		get_map(set, fd);
		free_split(set->tab, number_of_split(set->tab));
		set->tab = 0;
	}
	else
		ft_exit(set, "Error\nInvalid file\n");
}
