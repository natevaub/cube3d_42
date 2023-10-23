#include "../../includes/cube.h"

int	helper_valid_ceiling_color(char **ceilingValues, t_map *map)
{
	int	value;
	int	i;

	i = 0;
	while (ceilingValues[i] != NULL)
	{
		value = atoi(ceilingValues[i]);
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

int	helper_valid_floor_color(char **floorValues, t_map *map)
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

void	parse_elements(char *line, t_map *map)
{
	parse_east_texture(line, map);
	parse_west_texture(line, map);
	parse_north_texture(line, map);
	parse_south_texture(line, map);
	parse_floor(line, map);
	parse_ceiling(line, map);
}

int	map_start(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] && line[i] == '1')
		return (1);
	return (0);
}

char	*fill_map(char *line, t_map *map)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = ft_calloc(map->rows_width + 1, sizeof(char));
	if (new_line == NULL)
		return (NULL);
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i])
	{
		while (line[i] && j < map->rows_width)
		{
			if (line[i] == ' ')
				new_line[j] = '1';
			else
				new_line[j] = line[i];
			i++;
			j++;
		}
	}
	while (j < map->rows_width)
	{
		new_line[j] = '1';
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}
