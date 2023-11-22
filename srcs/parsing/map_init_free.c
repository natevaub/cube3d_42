
#include "../../includes/cube.h"

void init_map(t_map *map, char **av)
{
	map->path = ft_strdup(av[1]);
	map->so = NULL;
	map->no = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->count_no = 0;
	map->count_ea = 0;
	map->count_so = 0;
	map->count_we = 0;
	map->count_floor = 0;
	map->count_ceiling = 0;
	map->floor_R = -1;
	map->floor_G = -1;
	map->floor_B = -1;
	map->ceiling_R = -1;
	map->ceiling_G = -1;
	map->ceiling_B = -1;
	map->rows_count = 0;
	map->rows_width = 0;
	map->map_start_line = 0;
	map->map = NULL;
	map->copy = NULL;
}

void free_map(t_map *map)
{
	int i;

	free(map->path);
	if (map->copy)
	{
		if (map->player_position)
			free(map->player_position);
		free_split(map->copy);
		free(map->so);
		free(map->no);
		free(map->we);
		free(map->ea);
	}
	if (map->map)
	{
		i = 0;
		while (map->map[i])
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
}