/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 10:56:11 by mberne            #+#    #+#             */
/*   Updated: 2021/02/17 09:19:59 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strchr_gnl(const char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char	*get_buffer(char *str)
{
	int		i;
	char	*buffer;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	buffer = ft_substr(str, i + 1, (ft_strlen(str) - i));
	free(str);
	return (buffer);
}

char	*get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_substr(str, 0, i);
	return (line);
}

int		fill_buffer(char **buffer, int fd, int *return_read, char **tmp)
{
	while (ft_strchr_gnl(*buffer) == 0 && *return_read != 0)
	{
		if ((*return_read = read(fd, *tmp, BUFFER_SIZE)) == -1)
		{
			free(*tmp);
			return (-1);
		}
		(*tmp)[*return_read] = '\0';
		if (!(*buffer = ft_strjoin(*buffer, *tmp)))
			return (-1);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*buffer;
	char		*tmp;
	int			return_read;

	return_read = 1;
	if (BUFFER_SIZE <= 0 || fd < 0 || !line)
		return (-1);
	if (!(tmp = malloc((sizeof(char) * (BUFFER_SIZE + 1)))))
		return (-1);
	if (fill_buffer(&buffer, fd, &return_read, &tmp) == -1)
		return (-1);
	free(tmp);
	if (!(*line = get_line(buffer)))
		return (-1);
	if (!(buffer = get_buffer(buffer)))
		return (-1);
	if (return_read == 0)
	{
		free(buffer);
		buffer = NULL;
		return (0);
	}
	return (1);
}
