/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:47:14 by mberne            #+#    #+#             */
/*   Updated: 2021/03/08 14:09:35 by mberne           ###   ########lyon.fr   */
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
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	rgb = ft_split(set->tab[1], ',');
	// nombre de split et que des chiffres
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r > 255 || g > 255 || b > 255)
	{
		free_split(rgb, number_of_split(rgb));
		ft_exit(set, "Error\nInvalid color\n");
	}
	if (!ft_strncmp(set->tab[0], "F", 1) && set->floor == -1)
		set->floor = get_rgb(r, g, b);
	else if (!ft_strncmp(set->tab[0], "C", 1) && set->ceiling == -1)
		set->ceiling = get_rgb(r, g, b);
	else
	{
		free_split(rgb, number_of_split(rgb));
		ft_exit(set, "Error\nInvalid color\n");
	}
	free_split(rgb, number_of_split(rgb));
}

void	get_texture(t_settings *set)
{
	if (!ft_strncmp(set->tab[0], "NO", 2) && set->no == 0)
	{
		set->no = ft_strdup(set->tab[1]);
		if (!set->no)
			ft_exit(set, "");
	}
	else if (!ft_strncmp(set->tab[0], "SO", 2) && set->so == 0)
	{
		set->so = ft_strdup(set->tab[1]);
		if (!set->so)
			ft_exit(set, "");
	}
	else if (!ft_strncmp(set->tab[0], "WE", 2) && set->we == 0)
	{
		set->we = ft_strdup(set->tab[1]);
		if (!set->we)
			ft_exit(set, "");
	}
	else if (!ft_strncmp(set->tab[0], "EA", 2) && set->ea == 0)
	{
		set->ea = ft_strdup(set->tab[1]);
		if (!set->ea)
			ft_exit(set, "");
	}
	else if (!ft_strncmp(set->tab[0], "S", 1)
		&& ft_strncmp(set->tab[0], "SO", 2) && set->sprite == 0)
	{
		set->sprite = ft_strdup(set->tab[1]);
		if (!set->sprite)
			ft_exit(set, "");
	}
	else
		ft_exit(set, "Error\nInvalid textures\n");
}

void	get_resolution(t_settings *set)
{
	if (set->res[0] == -1 && set->res[1] == -1)
	{
		set->res[0] = ft_atoi(set->tab[1]);
		set->res[1] = ft_atoi(set->tab[2]);
		if (set->res[0] <= 0 || set->res[1] <= 0)
			ft_exit(set, "Error\nInvalid resolution\n");
	}
	else
		ft_exit(set, "Error\nInvalid resolution\n");
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
		if (*set->line)
		{
			set->tab = ft_split(set->line, ' ');
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
				get_map(set, fd);
			else
				ft_exit(set, "Error\nInvalid file\n");
			free(set->line);
			free_split(set->tab, number_of_split(set->tab));
		}
	}
}
