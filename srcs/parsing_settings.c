#include "cub3d.h"

unsigned int	get_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = r * 256 * 256;
	j = g * 256;
	k = b;
	return (i + j + k);
}

void	get_color(t_struct *as)
{
	char			**rgb;
	unsigned int	color[3];

	rgb = ft_split(as->set.tab[1], ',');
	if (!rgb)
		ft_exit(as, "Error\nMalloc error\n");
	if (number_of_split(rgb) != 3 || !ft_isnumber(rgb[0])
		|| !ft_isnumber(rgb[1]) || !ft_isnumber(rgb[2])
		|| ft_count(as->set.tab[1], ',') != 2)
	{
		free_split(rgb, number_of_split(rgb));
		ft_exit(as, "Error\nInvalid color\n");
	}
	color[0] = ft_atoi(rgb[0]);
	color[1] = ft_atoi(rgb[1]);
	color[2] = ft_atoi(rgb[2]);
	free_split(rgb, number_of_split(rgb));
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
		ft_exit(as, "Error\nInvalid color\n");
	if (!ft_strncmp(as->set.tab[0], "F", 1) && as->set.floor == -1)
		as->set.floor = get_rgb(color[0], color[1], color[2]);
	else if (!ft_strncmp(as->set.tab[0], "C", 1) && as->set.ceiling == -1)
		as->set.ceiling = get_rgb(color[0], color[1], color[2]);
	else
		ft_exit(as, "Error\nInvalid color\n");
}

void	get_texture(t_struct *as)
{
	if (!ft_strncmp(as->set.tab[0], "NO", 2) && as->set.text[0] == 0)
		as->set.text[0] = ft_strdup(as->set.tab[1]);
	else if (!ft_strncmp(as->set.tab[0], "EA", 2) && as->set.text[1] == 0)
		as->set.text[1] = ft_strdup(as->set.tab[1]);
	else if (!ft_strncmp(as->set.tab[0], "SO", 2) && as->set.text[2] == 0)
		as->set.text[2] = ft_strdup(as->set.tab[1]);
	else if (!ft_strncmp(as->set.tab[0], "WE", 2) && as->set.text[3] == 0)
		as->set.text[3] = ft_strdup(as->set.tab[1]);
	else
		ft_exit(as, "Error\nInvalid textures\n");
}

void	parsing(t_struct *as, int fd)
{
	if ((!ft_strncmp(as->set.tab[0], "NO", ft_strlen(as->set.tab[0]))
			|| !ft_strncmp(as->set.tab[0], "SO", ft_strlen(as->set.tab[0]))
			|| !ft_strncmp(as->set.tab[0], "WE", ft_strlen(as->set.tab[0]))
			|| !ft_strncmp(as->set.tab[0], "EA", ft_strlen(as->set.tab[0])))
		&& check_arg(&as->set, 2))
		get_texture(as);
	else if (check_arg(&as->set, 2)
		&& (!ft_strncmp(as->set.tab[0], "F", ft_strlen(as->set.tab[0]))
			|| !ft_strncmp(as->set.tab[0], "C", ft_strlen(as->set.tab[0]))))
		get_color(as);
	else if (!ft_strncmp(as->set.tab[0], "1", 1) || as->set.line[0] == ' ')
		map(as, fd);
	else
		ft_exit(as, "Error\nInvalid file\n");
}

void	get_settings(t_struct *as, int fd, int ret)
{
	fd = open(as->set.file, O_RDONLY);
	if (fd == -1)
		ft_exit(as, "Error\nFile failed to open\n");
	while (ret > 0)
	{
		ret = get_next_line(fd, &as->set.line);
		if (ret == -1)
			ft_exit(as, "Error\nAn error occured while reading file\n");
		if (*as->set.line)
		{
			as->set.tab = ft_split(as->set.line, ' ');
			if (!as->set.tab)
				ft_exit(as, "Error\nMalloc error\n");
			parsing(as, fd);
		}
		free(as->set.line);
		as->set.line = 0;
		free_split(as->set.tab, number_of_split(as->set.tab));
		as->set.tab = 0;
	}
	if (close(fd) == -1)
		ft_exit(as, "Error\nFile failed to close\n");
}
