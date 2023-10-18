#include "../../includes/cube.h"

// Function to check if a line contains elements that are not in the specification


int	cubParsing(char *path, t_map *map)
{
	int	res;

	res = openCubFile(path);
	if (res == -1)
	{
		return (0);
	}
	else
	{
		parseCubElements(res, map);
	}
	return (1);
}

int	openCubFile(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Cannot open ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	return (fd);
}

int	parseCubElements(int fd, t_map *map)
{
	char	*current_line;
	int		i = 0;
	int		start = 0;

	/* Iterate through the .cub file until it reaches the map */
	while ((current_line = get_next_line(fd)) != NULL && start == 0)
	{
		ft_printf("[ %s ]   [ %d ]\n", current_line, i);
		parseEastTexture(current_line, map);
		// parseWestTexture(current_line, map);
		// parseNorthTexture(current_line, map);
		// parseSouthTexture(current_line, map);
		// parseFloor(current_line, map);
		// parseCeiling(current_line, map);
		/* Function map_start */
		// start = mapStart(current_line);
		free(current_line);
		// i++;
	}
	/* Check if map contains all textures and colors before parsing map */

	if (isMapValid(map) == 0) {
		// Map is valid
		ft_printf("Map is valid\n");
	} else {
		// Map is invalid
		ft_printf("Map is invalid\n");
	}
	return (0);
}


// Helper function to itera through the .cub file until it reaches the map
/* *
Except for the map, each type of information from an element can be separated
by one or more space(s).
◦ The map must be parsed as it looks in the file. Spaces are a valid part of the
map and are up to you to handle. You must be able to parse any kind of map,
as long as it respects the rules of the map. 
*/
int	mapStart(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '1')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	unwantedElements(char *line)
{
	char	**test;

	test = ft_split(line, ' ');
	if (ft_strcmp(line, "WE") || ft_strcmp(line, "EA")
		|| ft_strcmp(line, "NO") || ft_strcmp(line, "SO")
		|| ft_strcmp(line, "S") || ft_strcmp(line, "F") || ft_strcmp(line, "C"))
	{
		free_split(test);
		return (1);
	}
	free_split(test);
	return (0);
}

int isMapValid(t_map *map)
{
	if (map->so == NULL || map->no == NULL || map->we == NULL || map->ea == NULL) {
		// At least one of the textures is NULL
		return (1);
	}
	if (map->count_no != 1 || map->count_ea != 1 || map->count_so != 1 || map->count_we != 1) {
		// One or more count fields are not equal to 1
		return (1);
	}
	if (map->floor_R == -1 || map->floor_G == -1 || map->floor_B == -1 ||
		map->ceiling_R == -1 || map->ceiling_G == -1 || map->ceiling_B == -1) {
		// One or more RGB values are -1
		return (1);
	}
	// All conditions are met
	return (0);
}
