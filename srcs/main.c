#include "../includes/cube.h"

void	debug_print_int_values(char *str) {
	if (!str) {
		return;
	}
	for (int i = 0; i < ft_strlen(str); i++) {
		ft_printf("%d ", str[i]);
	}
	ft_printf("\n");
}

void debug_print_map(const t_map *map) {
	printf("East Texture: %s\n", map->ea ? map->ea : "Not defined");
	printf("North Texture: %s\n", map->no ? map->no : "Not defined");
	printf("South Texture: %s\n", map->so ? map->so : "Not defined");
	printf("West Texture: %s\n", map->we ? map->we : "Not defined");

	printf("Floor Color: ");
	if (map->floor_R >= 0 && map->floor_G >= 0 && map->floor_B >= 0) {
		printf("%d,%d,%d\n", map->floor_R, map->floor_G, map->floor_B);
	} else {
		printf("Not defined\n");
	}

	printf("Ceiling Color: ");
	if (map->ceiling_R >= 0 && map->ceiling_G >= 0 && map->ceiling_B >= 0) {
		printf("%d,%d,%d\n", map->ceiling_R, map->ceiling_G, map->ceiling_B);
	} else {
		printf("Not defined\n");
	}

	printf("Texture Counts:\n");
	printf("East Texture Count: %d\n", map->count_ea);
	printf("North Texture Count: %d\n", map->count_no);
	printf("South Texture Count: %d\n", map->count_so);
	printf("West Texture Count: %d\n", map->count_we);

	printf("Ceiling Count: %d\n", map->count_ceiling);
	printf("Floor Count: %d\n", map->count_floor);

	printf("Rows Count: %d\n", map->rows_count);
	printf("Rows Width: %d\n", map->rows_width);
	printf("Map Copy:\n");

	printf("Map Content:\n");
	if (map->copy) {
		for (int i = 0; map->copy[i]; i++) {
			printf("%s\n", map->copy[i]);
		}
	} else {
		printf("Not defined\n");
	}


	printf("Map Content:\n");
	if (map->map) {
		for (int i = 0; map->map[i]; i++) {
			printf("%s\n", map->map[i]);
		}
	} else {
		printf("Not defined\n");
	}
}

void	init_map(t_map *map, char **av)
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

void	free_map(t_map *map)
{
	int	i;

	free(map->path);
	if (map->copy)
	{
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

int	main( int ac, char **av )
{
	t_map	map;
	int		code_error;

	init_map(&map, av);
	// open_cub_file(map.path, &map);
	code_error = parser(&map);
	ft_printf("Code error = %d\n", code_error);
	if (code_error)
	{
		debug_print_map(&map);
		free_map(&map);
		ft_printf("😔 Why are you doing this to me ? 😔\n");
		return (1);
	}
	else if (!code_error)
		ft_printf("🔥 I'm ready to cast rayzzzz 🔥\n");
	// debug_print_map(&map);
	free_map(&map);
	return (0);
}