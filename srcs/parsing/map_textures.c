#include "../../includes/cube.h"

/**
 * Parse the East Texture element from a line and store it in the map structure.
 *
 * This function parses a line of input containing information about the East
 * Texture element, validates the existence of the texture file, and stores
 * the path to the East Texture in the 'map' structure if valid.
 *
 * @param line A string containing the input line to be parsed.
 * @param map A pointer to the 't_map' structure where the East Texture path
 *            will be stored if valid.
 *
 * @return 1 if the East Texture was successfully parsed and stored, 0 otherwise.
 */
void	parse_east_texture(char *line, t_map *map)
{
	char	**texture_info;
	int		count_info;
	int		existing_file;

	texture_info = ft_split(line, ' ');
	if (map->count_ea > 1)
	{
		free_split(texture_info);
		return ;
	}
	count_info = count_split_elements(texture_info);
	if (ft_strcmp(texture_info[0], "EA") == 0)
	{
		map->count_ea++;
		if (count_info != 2)
		{
			free_split(texture_info);
			return ;
		}
		check_access_textures(texture_info, map, count_info);
		return ;
	}
	free_split(texture_info);
}

void	parse_west_texture(char *line, t_map *map)
{
	char	**texture_info;
	int		count_info;
	int		existing_file;

	texture_info = ft_split(line, ' ');
	if (map->count_we > 1)
	{
		free_split(texture_info);
		return ;
	}
	count_info = count_split_elements(texture_info);
	if (ft_strcmp(texture_info[0], "WE") == 0)
	{
		map->count_we++;
		if (count_info != 2)
		{
			free_split(texture_info);
			return ;
		}
		check_access_textures(texture_info, map, count_info);
		return ;
	}
	free_split(texture_info);
}

void	parse_north_texture(char *line, t_map *map)
{
	char	**texture_info;
	int		count_info;
	int		existing_file;

	texture_info = ft_split(line, ' ');
	if (map->count_no > 1)
	{
		free_split(texture_info);
		return ;
	}
	count_info = count_split_elements(texture_info);
	if (ft_strcmp(texture_info[0], "NO") == 0)
	{
		map->count_no++;
		if (count_info != 2)
		{
			free_split(texture_info);
			return ;
		}
		check_access_textures(texture_info, map, count_info);
		return ;
	}
	free_split(texture_info);
}

void	parse_south_texture(char *line, t_map *map)
{
	char	**texture_info;
	int		count_info;
	int		existing_file;

	texture_info = ft_split(line, ' ');
	if (map->count_so > 1)
	{
		free_split(texture_info);
		return ;
	}
	count_info = count_split_elements(texture_info);
	if (ft_strcmp(texture_info[0], "SO") == 0)
	{
		map->count_so++;
		if (count_info != 2)
		{
			free_split(texture_info);
			return ;
		}
		check_access_textures(texture_info, map, count_info);
		return ;
	}
	free_split(texture_info);
}

void	check_access_textures(char **texture_info, t_map *map, int count_info)
{
	char	*texture_types[4];
	char	**destinations[4];
	int		i;

	i = 0;
	texture_types[0] = "EA";
	texture_types[1] = "WE";
	texture_types[2] = "NO";
	texture_types[3] = "SO";
	destinations[0] = &(map->ea);
	destinations[1] = &(map->we);
	destinations[2] = &(map->no);
	destinations[3] = &(map->so);
	while (i < 4)
	{
		if (ft_strcmp(texture_info[0], texture_types[i]) == 0
			&& access(texture_info[1], F_OK) == 0)
		{
			*destinations[i] = ft_strdup(texture_info[1]);
			free_split(texture_info);
			return ;
		}
		i++;
	}
	free_split(texture_info);
}
