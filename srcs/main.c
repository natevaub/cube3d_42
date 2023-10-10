#include "../includes/cube.h"

int	main( int ac, char **av )
{
	t_map	map;

	// char texture[256] = "   EA     /home/nate/Workspace/42projects/cube3d_42/textures/xpm   ";
	// parseEastTexture(texture, &map);
	// ft_printf("EA Texture: %s\n", map.ea);

	char validColor[256] = "255,11,11";
	int res = validFloorColor(validColor, &map);
	ft_printf("Res = %d\n", res);
	ft_printf("In struct %d --- %d --- %d\n", map.floor_R, map.floor_G, map.floor_B);
	return 0;
}