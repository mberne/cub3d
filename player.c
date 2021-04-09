#include "cub3d.h"

void	player_spawn(t_struct *as)
{
	as->set.pposition[0] = 0;
	as->set.pposition[1] = 0;
	as->set.porientation = 'N';
	as->player.x = as->set.pposition[0];
	as->player.y = as->set.pposition[1];
	as->player.z = 0.5;
	if (as->set.porientation == 'N')
		as->player.rad = 0;
	else if (as->set.porientation == 'E')
		as->player.rad = 90 * (M_PI / 180);
	else if (as->set.porientation == 'S')
		as->player.rad = M_PI;
	else if (as->set.porientation == 'W')
		as->player.rad = 270 * (M_PI / 180);
}
