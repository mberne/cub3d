/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:15:29 by mberne            #+#    #+#             */
/*   Updated: 2020/11/30 10:05:26 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ns;
	char	*str;

	i = 0;
	str = (char *)s;
	if (s == 0)
		return (0);
	if (len > ft_strlen(str))
		len = ft_strlen(str);
	if (!(ns = malloc(sizeof(char) * (len + 1))))
		return (0);
	if (start >= ft_strlen(s))
	{
		ns[i] = 0;
		return (ns);
	}
	while (str[start] && i < len)
		ns[i++] = str[start++];
	ns[i] = '\0';
	return (ns);
}
