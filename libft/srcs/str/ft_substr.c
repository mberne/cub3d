/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:15:29 by mberne            #+#    #+#             */
/*   Updated: 2021/02/16 15:55:27 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ns;
	char	*str;
	size_t	len_str;

	i = 0;
	str = (char *)s;
	if (!s)
		return (0);
	len_str = ft_strlen(str);
	if (len_str < len)
		len = len_str;
	if (!(ns = malloc(sizeof(char) * len + 1)))
		return (0);
	if (start >= len_str)
	{
		ns[i] = 0;
		return (ns);
	}
	while (str[start] && i < len)
		ns[i++] = str[start++];
	ns[i] = '\0';
	return (ns);
}
