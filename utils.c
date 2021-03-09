/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 09:35:30 by mberne            #+#    #+#             */
/*   Updated: 2021/03/09 15:40:59 by mberne           ###   ########lyon.fr   */
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
	while (set->tab[j])
		j++;
	if (i == j)
		return (1);
	return (0);
}

int	ft_isnumber(char *s)
{
	int	i;
	int	j;

	i = ft_strlen(s);
	j = 0;
	while (ft_isdigit(s[j]))
		j++;
	if (i == j)
		return (1);
	return (0);
}

int	ft_count(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			i++;
		s++;
	}
	return (i);
}
