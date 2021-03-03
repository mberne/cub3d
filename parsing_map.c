/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:52:15 by mberne            #+#    #+#             */
/*   Updated: 2021/03/03 16:03:35 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map(t_settings *set)
{
	int	i;
	int	j;

	i = 0;
	while (set->map[i])
	{
		j = 0;
		while (set->map[i][j])
		{
			if (set->map[i][j] == '0' || set->map[i][j] == '2'
				|| set->map[i][j] == 'N' || set->map[i][j] == 'S'
				|| set->map[i][j] == 'E' || set->map[i][j] == 'W')
			{
				if (set->map[i - 1][j] == ' ' || set->map[i + 1][j] == ' '
					|| set->map[i][j - 1] == ' ' || set->map[i][j + 1] == ' ')
				{
					printf("Error\nInvalid map\n");
					free_split(set->map, number_of_split(set->map));
					exit(-1);
				}
			}
			j++;
		}
		i++;
	}
}

void	setup_map(t_settings *set)
{
	int	i;
	int	tmp;
	int	length;

	i = 0;
	length = 0;
	while (set->map[i])
	{
		tmp = ft_strlen(set->map[i]);
		if (tmp > length)
			length = tmp;
		i++;
	}
	i = 0;
	while (set->map[i])
	{
		tmp = ft_strlen(set->map[i]);
		if (tmp < length)
		{
			tmp = length - tmp;
			while (set->map[i][tmp])
			{
				set->map[i][tmp] = ' ';
				tmp++;
			}
		}
		i++;
	}
	int	j;
	j = 0;
	while (set->map[j])
	{
		printf("|%s|\n", set->map[j]);
		j++;
	}
}

void	get_map(t_settings *set, char *line, int fd)
{
	int		ret;
	char	*tmpmap;

	ret = 1;
	tmpmap = NULL;
	while (ret > 0)
	{
		if (*line)
		{
			tmpmap = ft_strjoin(tmpmap, line);
			tmpmap = ft_strjoin(tmpmap, "\n");
		}
		else
		{
			printf("Error\nInvalid map\n");
			free(line);
			free(tmpmap);
			exit(-1);
		}
		ret = get_next_line(fd, &line);
	}
	tmpmap = ft_strjoin(tmpmap, line);
	set->map = ft_split(tmpmap, '\n');
	free(tmpmap);
	setup_map(set);
	check_map(set);
}
