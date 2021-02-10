/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 08:54:58 by mberne            #+#    #+#             */
/*   Updated: 2020/11/25 10:34:06 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *ptr;

	if (!(ptr = malloc(count * size)))
		return (0);
	ft_bzero(ptr, count * size);
	return (ptr);
}
