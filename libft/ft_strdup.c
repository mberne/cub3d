/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:45:44 by mberne            #+#    #+#             */
/*   Updated: 2020/11/25 13:55:40 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *dst;

	if (!(dst = malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (0);
	ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
	return (dst);
}
