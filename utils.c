/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 09:35:30 by mberne            #+#    #+#             */
/*   Updated: 2021/02/24 09:55:56 by mberne           ###   ########lyon.fr   */
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

int		number_of_split(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			i++;
	}
	return (i);
}
