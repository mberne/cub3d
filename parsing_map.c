/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:52:15 by mberne            #+#    #+#             */
/*   Updated: 2021/03/03 10:41:12 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_map(t_settings *set, char *tmpmap)
{
	(void)set;
	(void)tmpmap;
	printf("");
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
			printf("Error\n");
			printf("Invalid map\n");
			exit(-1);
		}
		ret = get_next_line(fd, &line);
	}
	tmpmap = ft_strjoin(tmpmap, line);
	set->map = ft_split(tmpmap, '\n');
	check_map(set, tmpmap);
}
