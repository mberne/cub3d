#include "cub3d.h"

void	player_spawn(t_struct *as)
{
	as->player.x = (as->set.pposition[0] + 0.5);
	as->player.y = (as->set.pposition[1] + 0.5);
	as->player.z = 0.2;
	if (as->set.porientation == 'N')
		as->player.rad = 0;
	else if (as->set.porientation == 'E')
		as->player.rad = M_PI_2;
	else if (as->set.porientation == 'S')
		as->player.rad = M_PI;
	else if (as->set.porientation == 'W')
		as->player.rad = -M_PI_2;
}
