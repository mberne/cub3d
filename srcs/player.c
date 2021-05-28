#include "cub3d.h"

void	player_spawn(t_struct *as)
{
	as->player.x = (as->set.pposition[0] + 0.5);
	as->player.y = (as->set.pposition[1] + 0.5);
	as->player.z = 0.5;
	if (as->set.porientation == 'N')
		as->player.rad = 0;
	else if (as->set.porientation == 'E')
		as->player.rad = M_PI_2;
	else if (as->set.porientation == 'S')
		as->player.rad = M_PI;
	else if (as->set.porientation == 'W')
		as->player.rad = -M_PI_2;
}

void	player_move(t_struct *as)
{
	t_player	next_pos;

	if (as->key.t_left)
		as->player.rad = as->player.rad - M_PI * 0.015;
	if (as->key.t_right)
		as->player.rad = as->player.rad + M_PI * 0.015;
	if (as->key.front)
	{
		next_pos.x = as->player.x + sinf(as->player.rad) * 0.1;
		next_pos.y = as->player.y - cosf(as->player.rad) * 0.1;
		if (as->set.map[(int)as->player.y][(int)next_pos.x] != '1')
			as->player.x = next_pos.x;
		if (as->set.map[(int)next_pos.y][(int)as->player.x] != '1')
			as->player.y = next_pos.y;
	}
	if (as->key.back)
	{
		next_pos.x = as->player.x - sinf(as->player.rad) * 0.1;
		next_pos.y = as->player.y + cosf(as->player.rad) * 0.1;
		if (as->set.map[(int)as->player.y][(int)next_pos.x] != '1')
			as->player.x = next_pos.x;
		if (as->set.map[(int)next_pos.y][(int)as->player.x] != '1')
			as->player.y = next_pos.y;
	}
	player_move_next(as);
}

int	player_move_next(t_struct *as)
{
	t_player	next_pos;

	if (as->key.left)
	{
		next_pos.x = as->player.x - cosf(as->player.rad) * 0.1;
		next_pos.y = as->player.y - sinf(as->player.rad) * 0.1;
		if (as->set.map[(int)as->player.y][(int)next_pos.x] != '1')
			as->player.x = next_pos.x;
		if (as->set.map[(int)next_pos.y][(int)as->player.x] != '1')
			as->player.y = next_pos.y;
	}
	if (as->key.right)
	{
		next_pos.x = as->player.x + cosf(as->player.rad) * 0.1;
		next_pos.y = as->player.y + sinf(as->player.rad) * 0.1;
		if (as->set.map[(int)as->player.y][(int)next_pos.x] != '1')
			as->player.x = next_pos.x;
		if (as->set.map[(int)next_pos.y][(int)as->player.x] != '1')
			as->player.y = next_pos.y;
	}
	return (0);
}
