#include "../includes/cube.h"

void printMap(const t_map *map) {
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
	printf("Map Content: ");
	if (map->map) {
		for (int i = 0; map->map[i]; i++) {
			printf("%s\n", map->map[i]);
		}
	} else {
		printf("Not defined\n");
	}
}

void	init_map(t_map *map)
{
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
	map->map = NULL;
}

void	free_map(t_map *map)
{
	free(map->so);
	map->so = NULL;
	free(map->no);
	map->no = NULL;
	free(map->we);
	map->we = NULL;
	free(map->ea);
	map->ea = NULL;
	map->floor_R = -1;
	map->floor_G = -1;
	map->floor_B = -1;
	map->ceiling_R = -1;
	map->ceiling_G = -1;
	map->ceiling_B = -1;
	map->map = NULL;
}

int	main( int ac, char **av )
{
	t_map	map;

	init_map(&map);

	cubParsing(av[1], &map);

	printMap(&map);

	// free_map(&map);

	// void *mlx; // The magical mlx pointer
	// void *win; // The window pointer

	// // Initialize mlx
	// mlx = mlx_init();

	// // Create a window
	// win = mlx_new_window(mlx, 800, 600, "My First mlx Window");

	// // The window will stay open until you close it
	// mlx_loop(mlx);

	return (0);
}