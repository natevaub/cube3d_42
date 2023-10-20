#include "../../includes/cube.h"

int	helper_validCeilingColor(char **CeilingValues, t_map *map)
{
	int	value;
	int	i;

	i = 0;
	while (CeilingValues[i] != NULL)
	{
		value = atoi(CeilingValues[i]);
		if (value < 0 || value > 255)
		{
			return (0);
		}
		if (i == 0)
			map->ceiling_R = value;
		else if (i == 1)
			map->ceiling_G = value;
		else if (i == 2)
			map->ceiling_B = value;
		i++;
	}
	return (1);
}

int	helper_validFloorColor(char **floorValues, t_map *map)
{
	int	value;
	int	i;

	i = 0;
	while (floorValues[i] != NULL)
	{
		value = atoi(floorValues[i]);
		if (value < 0 || value > 255)
		{
			return (0);
		}
		if (i == 0)
			map->floor_R = value;
		else if (i == 1)
			map->floor_G = value;
		else if (i == 2)
			map->floor_B = value;
		i++;
	}
	return (1);
}