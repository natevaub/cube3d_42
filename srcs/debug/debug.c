#include "../includes/cube.h"

void debug_print_int_values(char *str)
{
	if (!str)
	{
		return;
	}
	for (int i = 0; i < ft_strlen(str); i++)
	{
		ft_printf("%d ", str[i]);
	}
	ft_printf("\n");
}

void debug_print_map(const t_map *map)
{
	printf("East Texture: %s\n", map->ea ? map->ea : "Not defined");
	printf("North Texture: %s\n", map->no ? map->no : "Not defined");
	printf("South Texture: %s\n", map->so ? map->so : "Not defined");
	printf("West Texture: %s\n", map->we ? map->we : "Not defined");

	printf("Floor Color: ");
	if (map->floor_R >= 0 && map->floor_G >= 0 && map->floor_B >= 0)
	{
		printf("%d,%d,%d\n", map->floor_R, map->floor_G, map->floor_B);
	}
	else
	{
		printf("Not defined\n");
	}
	printf("Ceiling Color: ");
	if (map->ceiling_R >= 0 && map->ceiling_G >= 0 && map->ceiling_B >= 0)
	{
		printf("%d,%d,%d\n", map->ceiling_R, map->ceiling_G, map->ceiling_B);
	}
	else
	{
		printf("Not defined\n");
	}

	printf("Texture Counts:\n");
	printf("East Texture Count: %d\n", map->count_ea);
	printf("North Texture Count: %d\n", map->count_no);
	printf("South Texture Count: %d\n", map->count_so);
	printf("West Texture Count: %d\n", map->count_we);

	printf("Ceiling Count: %d\n", map->count_ceiling);
	printf("Floor Count: %d\n", map->count_floor);

	printf("Rows Count: %d\n", map->rows);
	printf("Rows Width: %d\n", map->columns);
	printf("Map Copy:\n");
	printf("Map Content:\n");
	
	if (map->copy)
	{
		for (int i = 0; map->copy[i]; i++)
		{
			printf("%s\n", map->copy[i]);
		}
	}
	else
	{
		printf("Not defined\n");
	}

	printf("Map Content:\n");
	if (map->map)
	{
		for (int i = 0; map->map[i]; i++)
		{
			printf("%s\n", map->map[i]);
		}
	}
	else
	{
		printf("Not defined\n");
	}
}