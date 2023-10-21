#include "../../includes/cube.h"

// Function to check if a line contains elements that are not in the specification


int	cub_parsing(char *path, t_map *map)
{
	int	res;

	res = open_cub_file(path);
	if (res == -1)
	{
		return (0);
	}
	else
	{
		parse_cub_elements(res, map);
	}
	return (1);
}

int	open_cub_file(char *path)
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

int	parse_cub_elements(int fd, t_map *map)
{
	char	*current_line;
	char	*line;
	int		i = 0;
	int		start = 0;
	int		badElements = 0;

	/* Iterate through the .cub file until it reaches the map */
	while ((current_line = get_next_line(fd)) != NULL && mapStart != 1)
	{
		line = front_trim(current_line);
		if (line[0] == '\0')
		{
			free_lines(line, current_line);
			continue;
		}
		if (mapStart(line) == 1)
		{
			free_lines(line, current_line);
			break;
		}
		ft_printf("[ %s ]   [ %d ]\n", line, i);
		if (unwanted_elements(line) == 1)
		{
			badElements = 1;
			free_lines(line, current_line);
			break;
		}
		parseElements(line, map);
		/* Function map_start */
		free_lines(line, current_line);
		i++;
	}

	/* Check if map contains all textures and colors before parsing map */
	if (is_valid_elements(map) || badElements == 1)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	else {
		ft_printf("Lets parse the map\n");
	}

	/* Parse the map */


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
