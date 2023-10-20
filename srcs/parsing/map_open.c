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
	char	*line;
	int		i = 0;
	int		start = 0;

	/* Iterate through the .cub file until it reaches the map */
	while ((current_line = get_next_line(fd)) != NULL && !start)
	{
		line = front_trim(current_line);
		if (line[0] == '\0')
		{
			freeLines(line, current_line);
			continue;
		}
		if (mapStart(line) == 1)
		{
			freeLines(line, current_line);
			break;
		}
		ft_printf("[ %s ]   [ %d ]\n", line, i);
		print_int_values(line);
		if (unwantedElements(line) == 1)
		{
			print_int_values(line);
			freeLines(line, current_line);
			break;
		}
		parseElements(line, map);
		/* Function map_start */
		freeLines(line, current_line);
		i++;
	}

	/* Check if map contains all textures and colors before parsing map */
	if (isValidElements(map) == 1)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Missing textures or colors\n", 2);
		return (0);
	}
	else {
		ft_printf("Lets parse the map\n");
	}

	return (0);
}

int unwantedElements(char *line)
{
	char **test;

	test = ft_split(line, ' ');

	if (ft_strcmp(test[0], "WE") != 0 &&
		ft_strcmp(test[0], "EA") != 0 &&
		ft_strcmp(test[0], "SO") != 0 &&
		ft_strcmp(test[0], "NO") != 0 &&
		ft_strcmp(test[0], "F") != 0 &&
		ft_strcmp(test[0], "C") != 0 &&
		ft_strcmp(test[0], " ") != 0)
	{
		print_int_values(test[0]);
		free_split(test);
		return (1);
	}

	free_split(test);
	return (0);
}

int isValidElements(t_map *map)
{
	if (map->so == NULL || map->no == NULL || map->we == NULL || map->ea == NULL) {
		// At least one of the textures is NULL
		ft_printf("Here 1\n");
		return (1);
	}
	if (map->count_no != 1 || map->count_ea != 1 || map->count_so != 1 || map->count_we != 1) {
		// One or more count fields are not equal to 1
		ft_printf("Here 2\n");
		return (1);
	}
	if (map->floor_R == -1 || map->floor_G == -1 || map->floor_B == -1 ||
		map->ceiling_R == -1 || map->ceiling_G == -1 || map->ceiling_B == -1) {
		ft_printf("Here 3\n");
		// One or more RGB values are -1
		return (1);
	}
	// All conditions are met
	return (0);
}

int	mapStart(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
	{
		i++;
	}
	if (line[i] == '1')
	{
		return (1);
	}
	return (0);
}
