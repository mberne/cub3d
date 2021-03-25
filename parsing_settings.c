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
	if (!ft_strncmp(as->set.tab[0], "NO", 2) && as->set.no == 0)
		as->set.no = ft_strdup(as->set.tab[1]);
	else if (!ft_strncmp(as->set.tab[0], "SO", 2) && as->set.so == 0)
		as->set.so = ft_strdup(as->set.tab[1]);
	else if (!ft_strncmp(as->set.tab[0], "WE", 2) && as->set.we == 0)
		as->set.we = ft_strdup(as->set.tab[1]);
	else if (!ft_strncmp(as->set.tab[0], "EA", 2) && as->set.ea == 0)
		as->set.ea = ft_strdup(as->set.tab[1]);
	else if (!ft_strncmp(as->set.tab[0], "S", 1)
		&& ft_strncmp(as->set.tab[0], "SO", 2) && as->set.sprite == 0)
		as->set.sprite = ft_strdup(as->set.tab[1]);
	else
		ft_exit(as, "Error\nInvalid textures\n");
}

void	get_resolution(t_struct *as)
{
	int	screenx;
	int	screeny;

	mlx_get_screen_size(as->vars.mlx, &screenx, &screeny);
	if (as->set.res[0] == -1 && as->set.res[1] == -1
		&& ft_isnumber(as->set.tab[1]) && ft_isnumber(as->set.tab[2]))
	{
		as->set.res[0] = fminf(ft_atoi(as->set.tab[1]), screenx);
		as->set.res[1] = fminf(ft_atoi(as->set.tab[2]), screeny);
		if (as->set.res[0] <= 0 || as->set.res[1] <= 0)
			ft_exit(as, "Error\nInvalid resolution\n");
	}
	else
		ft_exit(as, "Error\nInvalid resolution\n");
}

void	parsing(t_struct *as, int fd)
{
	if (!ft_strncmp(as->set.tab[0], "R", ft_strlen(as->set.tab[0]))
		&& check_arg(&as->set, 3))
		get_resolution(as);
	else if ((!ft_strncmp(as->set.tab[0], "NO", ft_strlen(as->set.tab[0]))
			|| !ft_strncmp(as->set.tab[0], "SO", ft_strlen(as->set.tab[0]))
			|| !ft_strncmp(as->set.tab[0], "WE", ft_strlen(as->set.tab[0]))
			|| !ft_strncmp(as->set.tab[0], "EA", ft_strlen(as->set.tab[0]))
			|| !ft_strncmp(as->set.tab[0], "S", ft_strlen(as->set.tab[0])))
		&& check_arg(&as->set, 2))
		get_texture(as);
	else if (check_arg(&as->set, 2)
		&& (!ft_strncmp(as->set.tab[0], "F", ft_strlen(as->set.tab[0]))
			|| !ft_strncmp(as->set.tab[0], "C", ft_strlen(as->set.tab[0]))))
		get_color(as);
	else if (!ft_strncmp(as->set.tab[0], "1", 1))
	{
		map(as, fd);
		free_split(as->set.tab, number_of_split(as->set.tab));
		as->set.tab = 0;
	}
	else
		ft_exit(as, "Error\nInvalid file\n");
}
