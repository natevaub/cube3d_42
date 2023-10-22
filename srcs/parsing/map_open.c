#include "../../includes/cube.h"

int	open_cub_file(char *path, t_map *map)
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
	else
	{
		cub_copy(fd, map);
	}
	return (0);
}

int	cub_copy(int fd, t_map *map)
{
	char	*line;
	char	*to_free;
	char	*res;
	int 	map_start_at;
	int		i;

	res = NULL;
	to_free = ft_strdup("");
	while ((line = get_next_line(fd)) != NULL)
	{
		res = ft_strjoin(to_free, line);
		free(to_free);
		to_free = res;
		free(line);
	}
	/* Detect if there's a map in the file */
	search_map(0, &map_start_at, res);
	if (map_start_at == -1)
	{
		ft_printf("Error map not found\n");
		return (0);
	}
	/* Detect if there's an empty line in the file */
	if (found_empty_line(&res[map_start_at]))
	{
		ft_printf("Error empty line in map\n");
		return (0);
	}

	/* Split res and store the result in copy */
	map->copy = ft_split(res, '\n');
	free(res);
	for (int i = 0; map->copy[i]; i++)
	{
		ft_printf("Line[%d]: [%s]\n", i, map->copy[i]);
	}
	i = 0;
	while (map->copy[i])
	{
		line = front_trim(map->copy[i]);
		if (mapStart(line))
		{
			ft_printf("Map found\n");
			break ;
		}
		if (unwanted_elements(line))
		{
			ft_printf("Line = %s\n", line);
			ft_printf("Error unwanted elements\n");
			return (0);
		}
		parseElements(line, map);
		free(line);
		i++;
	}
	printMap(map);
	if (!is_valid_elements(map))
	{
		ft_printf("Error invalid elements\n");
		return (0);
	}
	ft_printf("i = %d\n", i);
	return (0);
}
