#include "../includes/cube.h"

int	parseFloor(char *line, t_map *map)
{
	char	**floor_info;
	int		count_info;

	floor_info = ft_split(line, ' ');
	count_info = count_split_elements(floor_info);
	if (count_info == 2)
	{
		if (ft_strcmp(floor_info[0], "F") == 0)
		{
			/* Function to check that there is only digits and ',' char in floor_info[1] */
			/* && that there is 2 striclty to ',' seperating the 3 values */
			/* Valid floor_info[0] = "255,0,0" Not valid floor_info = ",255,120,0";
			/* Value should be between 0 and 255 */
			if (validFloorColor(floor_info[1], map) == 1)
			{

			}
			else
			{

			}
		}
	}
	free_split(floor_info);
	return (0);
}

int	validFloorColor(char *floorValues, t_map *map)
{
	char	**parsedRGB;
	int		count_info;
	int		i;
	int		j;

	i = -1;
	if (count_occurences(floorValues, ',') != 2)
		return (0);
	while (floorValues[++i] != '\0')
	{
		if (ft_isdigit(floorValues[i]) == 0 && floorValues[i] != ',')
			return (0);
	}
	parsedRGB = ft_split(floorValues, ',');
	count_info = count_split_elements(parsedRGB);
	if (count_info != 3)
		return (0);
	if (helper_validFloorColor(parsedRGB, map) == 0)
		return (0);
	free_split(parsedRGB);
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