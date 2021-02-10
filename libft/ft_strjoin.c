/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:04:28 by mberne            #+#    #+#             */
/*   Updated: 2020/11/25 15:44:36 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*ns;

	i = 0;
	j = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	if (!(ns = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2) + 1)))))
		return (0);
	while (s1[i])
	{
		ns[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ns[i + j] = s2[j];
		j++;
	}
	ns[i + j] = '\0';
	return (ns);
}
