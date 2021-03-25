#include "cub3d.h"

int	check_wall(t_struct *as, int i, int j)
{
	if (i == 0 || i == as->set.mapy || j == 0 || j == as->set.mapx
		|| as->set.map[i - 1][j] == ' ' || as->set.map[i + 1][j] == ' '
		|| as->set.map[i][j - 1] == ' ' || as->set.map[i][j + 1] == ' ')
		return (1);
	return (0);
}

void	check_map(t_struct *as)
{
	int	i;
	int	j;

	i = -1;
	while (as->set.map[++i])
	{
		j = -1;
		while (as->set.map[i][++j])
		{
			if (ft_strchr("02NSEW", as->set.map[i][j]) && check_wall(as, i, j))
				ft_exit(as, "Error\nInvalid map\n");
			if (ft_strchr("NSEW", as->set.map[i][j]) && !as->set.porientation)
			{
				as->set.pposition[0] = i;
				as->set.pposition[1] = j;
				as->set.porientation = as->set.map[i][j];
			}
			else if (ft_strchr("NSEW", as->set.map[i][j])
				&& as->set.porientation)
				ft_exit(as, "Error\nInvalid map\n");
		}
	}
	if (!as->set.porientation)
		ft_exit(as, "Error\nInvalid map\n");
}

void	setup_map(t_struct *as)
{
	int	i;
	int	tmp;

	i = -1;
	while (as->set.map[++i])
	{
		tmp = ft_strlen(as->set.map[i]);
		as->set.mapx = fmaxf(tmp, as->set.mapx);
	}
	i = -1;
	while (as->set.map[++i])
	{
		tmp = ft_strlen(as->set.map[i]);
		if (tmp < as->set.mapx)
		{
			while (tmp++ < as->set.mapx)
			{
				as->set.map[i] = ft_strjoin(as->set.map[i], " ");
				if (!as->set.map[i])
					ft_exit(as, "Error\nMalloc error\n");
			}
		}
	}
	as->set.mapx -= 1;
}

char	*create_map(t_struct *as, char *tmpmap, int fd)
{
	int	ret;

	ret = 1;
	while (ret > 0)
	{
		tmpmap = ft_strjoin(tmpmap, as->set.line);
		if (!tmpmap)
		{
			free(tmpmap);
			ft_exit(as, "Error\nMalloc error\n");
		}
		tmpmap = ft_strjoin(tmpmap, "\n");
		if (!tmpmap)
		{
			free(tmpmap);
			ft_exit(as, "Error\nMalloc error\n");
		}
		ret = get_next_line(fd, &as->set.line);
	}
	tmpmap = ft_strjoin(tmpmap, as->set.line);
	if (tmpmap)
		return (tmpmap);
	free(tmpmap);
	ft_exit(as, "Error\nMalloc error\n");
	return (NULL);
}

void	map(t_struct *as, int fd)
{
	char	*tmpmap;
	int		i;

	tmpmap = NULL;
	i = 0;
	tmpmap = create_map(as, tmpmap, fd);
	while (tmpmap[i])
	{
		if ((tmpmap[i] == '\n' && tmpmap[i + 1] == '\n'
				&& !(tmpmap[i + 2] == '\n' || tmpmap[i + 2] == '\0'))
			|| !ft_strchr(" 012NSWE\n", tmpmap[i]))
			ft_exit(as, "Error\nInvalid map\n");
		i++;
	}
	as->set.map = ft_split(tmpmap, '\n');
	free(tmpmap);
	as->set.mapy = number_of_split(as->set.map) - 1;
	setup_map(as);
	check_map(as);
}
