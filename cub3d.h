/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:23:34 by mberne            #+#    #+#             */
/*   Updated: 2021/03/03 10:38:47 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft/includes/libft.h"

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_settings
{
	char			*file;
	int				res[2];
	int				get_res;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sprite;
	unsigned int	floor;
	int				get_floor;
	unsigned int	ceiling;
	int				get_ceiling;
	char			**map;
}				t_settings;

int				main(int ac, char **av);
void			init_struct(t_settings *set);
void			get_settings(t_settings *set);
void			get_texture(t_settings *set, char **tab);
void			get_color(t_settings *set, char **tab);
unsigned int	get_rgb(int r, int g, int b);
void			get_map(t_settings *set, char *line, int fd);
void			check_map(t_settings *set, char *tmpmap);
void			free_split(char **tab, int i);
int				number_of_split(char **tab);

#endif
