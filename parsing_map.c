/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:52:15 by mberne            #+#    #+#             */
/*   Updated: 2021/03/09 15:41:06 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall(t_settings *set, int i, int j)
{
	if (i == 0 || i == set->mapy || j == 0 || j == set->mapx
		|| set->map[i - 1][j] == ' ' || set->map[i + 1][j] == ' '
		|| set->map[i][j - 1] == ' ' || set->map[i][j + 1] == ' ')
		return (1);
	return (0);
}

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
			if (ft_strchr("02NSEW", set->map[i][j]) && check_wall(set, i, j))
				ft_exit(set, "Error\nInvalid map\n");
			if (ft_strchr("NSEW", set->map[i][j]) && !set->porientation)
			{
				set->pposition[0] = i;
				set->pposition[1] = j;
				set->porientation = set->map[i][j];
			}
			else if (ft_strchr("NSEW", set->map[i][j]) && set->porientation)
				ft_exit(set, "Error\nInvalid map\n");
		}
	}
	if (!set->porientation)
		ft_exit(set, "Error\nInvalid map\n");
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
				if (!set->map[i])
					ft_exit(set, "Error\nMalloc error\n");
				tmp++;
			}
		}
	}
}

void	get_map(t_settings *set, int fd)
{
	int		ret;
	char	*tmpmap;

	ret = 1;
	tmpmap = NULL;
	while (ret > 0)
	{
		if (*set->line)
		{
			tmpmap = ft_strjoin(tmpmap, set->line);
			if (!tmpmap)
			{
				free(tmpmap);
				ft_exit(set, "Error\nMalloc error\n");
			}
			tmpmap = ft_strjoin(tmpmap, "\n");
			if (!tmpmap)
			{
				free(tmpmap);
				ft_exit(set, "Error\nMalloc error\n");
			}
		}
		else
		{
			free(tmpmap);
			ft_exit(set, "Error\nInvalid map\n");
		}
		ret = get_next_line(fd, &set->line);
	}
	tmpmap = ft_strjoin(tmpmap, set->line);
	if (!tmpmap)
	{
		free(tmpmap);
		ft_exit(set, "Error\nMalloc error\n");
	}
	set->map = ft_split(tmpmap, '\n');
	free(tmpmap);
	set->mapy = number_of_split(set->map) - 1;
	setup_map(set);
	set->mapx -= 1;
	check_map(set);
}
