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
void	parseEastTexture(char *line, t_map *map)
{
	char	**texture_info;
	char	*s;
	int		count_info;
	int		existing_file;

	texture_info = ft_split(line, ' ');
	if (texture_info == NULL)
		return;
	s = texture_info[1];
	texture_info[1] = ft_strtrim(texture_info[1], " \n");
	free(s);
	count_info = count_split_elements(texture_info);
	if (ft_strcmp(texture_info[0], "EA") == 0)
	{
		map->count_ea++;
		if (count_info == 2)
		{
			if (access(texture_info[1], F_OK) == 0)
			{
				map->ea = ft_strdup(texture_info[1]);
				free_split(texture_info);
				return;
			}
			else
			{
				free_split(texture_info);
				return;
			}
		}
	}
	free_split(texture_info);
	return;
}

void	parseWestTexture(char *line, t_map *map)
{
	char	**texture_info;
	char	*s;
	int		count_info;
	int		existing_file;

	texture_info = ft_split(line, ' ');
	if (texture_info == NULL)
		return;
	s = texture_info[1];
	texture_info[1] = ft_strtrim(texture_info[1], " \n");
	free(s);
	count_info = count_split_elements(texture_info);
	if (ft_strcmp(texture_info[0], "WE") == 0)
	{
		map->count_we++;
		if (count_info == 2)
		{
			if (access(texture_info[1], F_OK) == 0)
			{
				map->we = ft_strdup(texture_info[1]);
				free_split(texture_info);
				return;
			}
			else
			{
				free_split(texture_info);
				return;
			}
		}
	}
	free_split(texture_info);
	return;
}

void	parseNorthTexture(char *line, t_map *map)
{
	char	**texture_info;
	char	*s;
	int		count_info;
	int		existing_file;

	texture_info = ft_split(line, ' ');
	if (texture_info == NULL)
		return;
	s = texture_info[1];
	texture_info[1] = ft_strtrim(texture_info[1], " \n");
	free(s);
	count_info = count_split_elements(texture_info);
	if (ft_strcmp(texture_info[0], "NO") == 0)
	{
		map->count_no++;
		if (count_info == 2)
		{
			if (access(texture_info[1], F_OK) == 0)
			{
				map->no = ft_strdup(texture_info[1]);
				free_split(texture_info);
				return;
			}
			else
			{
				free_split(texture_info);
				return;
			}
		}
	}
	free_split(texture_info);
	return;
}

void	parseSouthTexture(char *line, t_map *map)
{
	char	**texture_info;
	char	*s;
	int		count_info;
	int		existing_file;

	texture_info = ft_split(line, ' ');
	if (texture_info == NULL)
		return;
	s = texture_info[1];
	texture_info[1] = ft_strtrim(texture_info[1], " \n");
	// print_int_values(texture_info[1]);
	free(s);
	count_info = count_split_elements(texture_info);
	if (ft_strcmp(texture_info[0], "SO") == 0)
	{
		map->count_so++;
		if (count_info == 2)
		{
			if (access(texture_info[1], F_OK) == 0)
			{
				map->so = ft_strdup(texture_info[1]);
				free_split(texture_info);
				return;
			}
			else
			{
				free_split(texture_info);
				return;
			}
		}
	}
	free_split(texture_info);
	return;
}