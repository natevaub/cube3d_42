#include "../includes/cube.h"

void	parseFloor(char *line, t_map *map)
{
	char	**floor_info;
	int		count_info;

	floor_info = ft_split(line, ' ');
	if (floor_info == NULL)
		return;
	count_info = count_split_elements(floor_info);
	if (map->count_floor > 1)
	{
		free_split(floor_info);
		return;
	}
	if (ft_strcmp(floor_info[0], "F") == 0)
	{
		if (count_info == 2)
		{
			map->count_floor++;
			if (validFloorColor(floor_info[1], map) == 1)
			{
				free_split(floor_info);
				return;
			}
			else
			{
				free_split(floor_info);
				return;
			}
		}
	}
	free_split(floor_info);
	return;
}

void	parseCeiling(char *line, t_map *map)
{
	char	**ceiling_info;
	int		count_info;

	ceiling_info = ft_split(line, ' ');
	if (ceiling_info == NULL)
		return;
	count_info = count_split_elements(ceiling_info);
	if (map->count_ceiling > 1)
	{
		free_split(ceiling_info);
		return;
	}
	if (ft_strcmp(ceiling_info[0], "C") == 0)
	{
		map->count_ceiling++;
		
		if (count_info == 2)
		{
			if (validCeilingColor(ceiling_info[1], map) == 1)
			{
				free_split(ceiling_info);
				return;
			}
			else
			{
				free_split(ceiling_info);
				return;
			}
		}
	}
	free_split(ceiling_info);
	// free(ceiling_info);
	return;
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
	// free(parsedRGB);
	return (1);
}

int	validCeilingColor(char *ceilingValues, t_map *map)
{
	char	**parsedRGB;
	int		count_info;
	int		i;
	int		j;

	i = -1;
	if (count_occurences(ceilingValues, ',') != 2)
		return (0);
	while (ceilingValues[++i] != '\0')
	{
		if (ft_isdigit(ceilingValues[i]) == 0 && ceilingValues[i] != ',')
			return (0);
	}
	parsedRGB = ft_split(ceilingValues, ',');
	count_info = count_split_elements(parsedRGB);
	if (count_info != 3)
		return (0);
	if (helper_validCeilingColor(parsedRGB, map) == 0)
		return (0);
	free_split(parsedRGB);
	// free(parsedRGB);
	return (1);
}

void	freeLines(char *line, char *current_line)
{
	free(line);
	free(current_line);
}