#include "../../includes/cube.h"

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

	while ((current_line = get_next_line(fd)) != NULL)
	{
		ft_printf("Line Parsed = %s ---> i = %d\n", current_line, i);
		parseEastTexture(current_line, map);
		parseWestTexture(current_line, map);
		parseNorthTexture(current_line, map);
		parseSouthTexture(current_line, map);
		parseFloor(current_line, map);
		parseCeiling(current_line, map);
		free(current_line);
	}
	return (0);
}