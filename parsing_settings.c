/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:47:14 by mberne            #+#    #+#             */
/*   Updated: 2021/03/03 16:03:14 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_rgb(int r, int g, int b)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = (unsigned int)r * 256 * 256;
	j = (unsigned int)g * 256;
	k = (unsigned int)b;
	return (i + j + k);
}

void	get_color(t_settings *set, char **tab)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(tab[1], ',');
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("Error\nInvalid color\n");
		free_split(tab, number_of_split(tab));
		free_split(rgb, number_of_split(rgb));
		exit(-1);
	}
	if (!ft_strncmp(tab[0], "F", 1) && set->get_floor == 0)
	{
		set->floor = get_rgb(r, g, b);
		set->get_floor = 1;
	}
	else if (!ft_strncmp(tab[0], "C", 1) && set->get_ceiling == 0)
	{
		set->ceiling = get_rgb(r, g, b);
		set->get_ceiling = 1;
	}
	else
	{
		printf("Error\nInvalid color\n");
		free_split(tab, number_of_split(tab));
		free_split(rgb, number_of_split(rgb));
		exit(-1);
	}
	free_split(rgb, number_of_split(rgb));
}

void	get_texture(t_settings *set, char **tab)
{
	// verifier seulement tab[0] et tab [1] existent ?
	if (!ft_strncmp(tab[0], "NO", 2) && set->no == 0)
		set->no = ft_strdup(tab[1]);
	else if (!ft_strncmp(tab[0], "SO", 2) && set->so == 0)
		set->so = ft_strdup(tab[1]);
	else if (!ft_strncmp(tab[0], "WE", 2) && set->we == 0)
		set->we = ft_strdup(tab[1]);
	else if (!ft_strncmp(tab[0], "EA", 2) && set->ea == 0)
		set->ea = ft_strdup(tab[1]);
	else if (!ft_strncmp(tab[0], "S", 1) && ft_strncmp(tab[0], "SO", 2)
		&& set->sprite == 0)
		set->sprite = ft_strdup(tab[1]);
	else
	{
		printf("Error\nInvalid textures\n");
		free_split(tab, number_of_split(tab));
		exit(-1);
	}
}

void	get_resolution(t_settings *set, char **tab)
{
	if (set->get_res == 0)
	{
		set->res[0] = ft_atoi(tab[1]);
		set->res[1] = ft_atoi(tab[2]);
		if (set->res[0] == 0 || set->res[1] == 0)
		{
			printf("Error\nInvalid resolution\n");
			free_split(tab, number_of_split(tab));
			exit(-1);
		}
		set->get_res = 1;
	}
	else
	{
		printf("Error\nInvalid resolution\n");
		free_split(tab, number_of_split(tab));
		exit(-1);
	}
}

void	get_settings(t_settings *set)
{
	char	*line;
	int		fd;
	char	**tab;
	int		ret;

	line = NULL;
	fd = open(set->file, O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (*line)
		{
			tab = ft_split(line, ' ');
			if (!ft_strncmp(tab[0], "R", 1))
				get_resolution(set, tab);
			else if (!ft_strncmp(tab[0], "NO", 2)
				|| !ft_strncmp(tab[0], "SO", 2) || !ft_strncmp(tab[0], "WE", 2)
				|| !ft_strncmp(tab[0], "EA", 2) || !ft_strncmp(tab[0], "S", 1))
				get_texture(set, tab);
			else if (!ft_strncmp(tab[0], "F", 1) || !ft_strncmp(tab[0], "C", 1))
				get_color(set, tab);
			// pas jolie l'erreur invalid file alors que c'est erreur de map si elle commence par un 0...
			else if (!ft_strncmp(tab[0], "1", 1))
				get_map(set, line, fd);
			else
			{
				printf("Error\nInvalid file\n");
				free(line);
				free_split(tab, number_of_split(tab));
				exit(-1);
			}
			free(line);
			free_split(tab, number_of_split(tab));
		}
	}
}
