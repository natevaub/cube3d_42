#include "../includes/cube.h"

int	unwanted_elements(char *line)
{
	char	**test;

	test = ft_split(line, ' ');
	if (ft_strcmp(test[0], "WE") != 0
		&& ft_strcmp(test[0], "EA") != 0
		&& ft_strcmp(test[0], "SO") != 0
		&& ft_strcmp(test[0], "NO") != 0
		&& ft_strcmp(test[0], "F") != 0
		&& ft_strcmp(test[0], "C") != 0
		&& ft_strcmp(test[0], " ") != 0)
	{
		free_split(test);
		return (1);
	}
	free_split(test);
	return (0);
}

int	is_valid_elements(t_map *map)
{
	if (map->count_no != 1 || map->count_ea != 1 || map->count_so != 1
		|| map->count_we != 1)
	{
		ft_printf("Error: invalid number of textures\n");
		return (0);
	}
	if (map->so == NULL || map->no == NULL || map->we == NULL
		|| map->ea == NULL)
	{
		ft_printf("Error: invalid texture path\n");
		return (0);
	}
	if (map->count_floor != 1 || map->count_ceiling != 1)
	{
		ft_printf("Error: invalid number of colors\n");
		return (0);
	}
	if (map->floor_R == -1 || map->floor_G == -1 || map->floor_B == -1
		|| map->ceiling_R == -1 || map->ceiling_G == -1 || map->ceiling_B == -1)
	{
		ft_printf("Error: invalid color\n");
		return (0);
	}
	return (1);
}
