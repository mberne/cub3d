/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:52:15 by mberne            #+#    #+#             */
/*   Updated: 2021/03/04 11:27:56 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map(t_settings *set)
{
	int	i;
	int	j;

	i = -1;
	while (set->map[++i])
	{
		j = -1;
		while (set->map[i][++j])
		{
			if (set->map[i][j] == '0' || set->map[i][j] == '2'
				|| set->map[i][j] == 'N' || set->map[i][j] == 'S'
				|| set->map[i][j] == 'E' || set->map[i][j] == 'W')
			{
				if (i == 0 || i == set->mapy || j == 0 || j == set->mapx
					|| set->map[i - 1][j] == ' ' || set->map[i + 1][j] == ' '
					|| set->map[i][j - 1] == ' ' || set->map[i][j + 1] == ' ')
				{
					printf("Error\nInvalid map\n");
					free_split(set->map, set->mapy);
					exit(-1);
				}
			}
		}
	}
}

void	setup_map(t_settings *set)
{
	int	i;
	int	tmp;

	i = -1;
	while (set->map[++i])
	{
		tmp = ft_strlen(set->map[i]);
		if (tmp > set->mapx)
			set->mapx = tmp;
	}
	i = -1;
	while (set->map[++i])
	{
		tmp = ft_strlen(set->map[i]);
		if (tmp < set->mapx)
		{
			while (tmp < set->mapx)
			{
				set->map[i] = ft_strjoin(set->map[i], " ");
				if (!(set->map[i]))
					exit(-1);
				tmp++;
			}
		}
	}
	set->mapx -= 1;
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
	set->mapy = number_of_split(set->map) - 1;
	setup_map(set);
	check_map(set);
}
