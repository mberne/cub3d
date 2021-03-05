/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 09:35:30 by mberne            #+#    #+#             */
/*   Updated: 2021/03/05 16:07:50 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **tab, int i)
{
	if (tab)
	{
		while (--i >= 0)
			free(tab[i]);
		free(tab);
	}
}

int	number_of_split(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		while (tab[i])
			i++;
	return (i);
}

int	check_arg(t_settings *set, int i)
{
	int	j;

	j = 0;
	while (set->split[j])
		j++;
	if (i == j)
		return (1);
	return (0);
}

void	ft_exit(t_settings *set, char *str)
{
	printf("%s", str);
	if (set->split)
		free_split(set->split, number_of_split(set->split));
	if (set->map)
		free_split(set->map, number_of_split(set->map));
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
	exit(-1);
}
