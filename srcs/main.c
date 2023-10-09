#include "../includes/cube.h"

int	main( int ac, char **av )
{
	t_map	map;

	char texture[256] = "   EA     /home/nate/Workspace/42projects/cube3d_42/textures/xpm   ";
	parseEastTexture(texture, &map);
	ft_printf("EA Texture: %s\n", map.ea);
	return 0;
}