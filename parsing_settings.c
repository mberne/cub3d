/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:47:14 by mberne            #+#    #+#             */
/*   Updated: 2021/03/05 16:10:33 by mberne           ###   ########lyon.fr   */
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

	rgb = ft_split(set->split[1], ',');
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (rgb[3] != 0 || r > 255 || g > 255 || b > 255)
	{
		free_split(rgb, number_of_split(rgb));
		ft_exit(set, "Error\nInvalid color\n");
	}
	if (!ft_strncmp(set->split[0], "F", 1) && set->get_floor == 0)
	{
		set->floor = get_rgb(r, g, b);
		set->get_floor = 1;
	}
	else if (!ft_strncmp(set->split[0], "C", 1) && set->get_ceiling == 0)
	{
		set->ceiling = get_rgb(r, g, b);
		set->get_ceiling = 1;
	}
	else
	{
		free_split(rgb, number_of_split(rgb));
		ft_exit(set, "Error\nInvalid color\n");
	}
	free_split(rgb, number_of_split(rgb));
}

void	get_texture(t_settings *set)
{
	if (!ft_strncmp(set->split[0], "NO", 2) && set->no == 0)
	{
		set->no = ft_strdup(set->split[1]);
		if (!set->no)
			ft_exit(set, "");
	}
	else if (!ft_strncmp(set->split[0], "SO", 2) && set->so == 0)
	{
		set->so = ft_strdup(set->split[1]);
		if (!set->so)
			ft_exit(set, "");
	}
	else if (!ft_strncmp(set->split[0], "WE", 2) && set->we == 0)
	{
		set->we = ft_strdup(set->split[1]);
		if (!set->we)
			ft_exit(set, "");
	}
	else if (!ft_strncmp(set->split[0], "EA", 2) && set->ea == 0)
	{
		set->ea = ft_strdup(set->split[1]);
		if (!set->ea)
			ft_exit(set, "");
	}
	else if (!ft_strncmp(set->split[0], "S", 1)
		& ft_strncmp(set->split[0], "SO", 2)
		&& set->sprite == 0)
	{
		set->sprite = ft_strdup(set->split[1]);
		if (!set->sprite)
			ft_exit(set, "");
	}
	else
		ft_exit(set, "Error\nInvalid textures\n");
}

void	get_resolution(t_settings *set)
{
	if (set->get_res == 0)
	{
		set->res[0] = ft_atoi(set->split[1]);
		set->res[1] = ft_atoi(set->split[2]);
		if (set->res[0] <= 0 || set->res[1] <= 0)
			ft_exit(set, "Error\nInvalid resolution\n");
		set->get_res = 1;
	}
	else
		ft_exit(set, "Error\nInvalid resolution\n");
}

void	get_settings(t_settings *set)
{
	char	*line;
	int		fd;
	int		ret;

	line = NULL;
	fd = open(set->file, O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (*line)
		{
			set->split = ft_split(line, ' ');
			if (!ft_strncmp(set->split[0], "R", 1) && check_arg(set->split, 3))
				get_resolution(set);
			else if ((!ft_strncmp(set->split[0], "NO", 2)
					|| !ft_strncmp(set->split[0], "SO", 2)
					|| !ft_strncmp(set->split[0], "WE", 2)
					|| !ft_strncmp(set->split[0], "EA", 2)
					|| !ft_strncmp(set->split[0], "S", 1))
				&& check_arg(set->split, 2))
				get_texture(set);
			else if (check_arg(set->split, 2)
				&& (!ft_strncmp(set->split[0], "F", 1)
					|| !ft_strncmp(set->split[0], "C", 1)))
				get_color(set);
			else if (!ft_strncmp(set->split[0], "1", 1))
				get_map(set, line, fd);
			else
			{
				free(line);
				ft_exit(set, "Error\nInvalid file\n");
			}
			free(line);
			free_split(set->split, number_of_split(set->split));
		}
	}
}
