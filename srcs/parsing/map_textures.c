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
int	parseEastTexture(char *line, t_map *map)
{
	char	**texture_info;
	int		count_info;
	int		existing_file;

	texture_info = ft_split(line, ' ');
	if (texture_info == NULL)
		return (0);
	// texture_info[1] = ft_strtrim(texture_info[1], "\n");
	ft_printf("EA Texture: %s\n", texture_info[1]);
	count_info = count_split_elements(texture_info);
	ft_printf("Info = %d\n", count_info);
	if (count_info == 2)
	{
		if (ft_strcmp(texture_info[0], "EA") == 0)
		{
			/* Function to check that files extension is .xpm */
			if (access(texture_info[1], F_OK) == 0)
			{
				map->ea = ft_strdup(texture_info[1]);
				free_split(texture_info);
				ft_printf("Success\n");
				return (1);
			}
			else
			{
				free_split(texture_info);
				ft_printf("Texture not found\n");
				return(0);
			}
		}
	}
	ft_printf("Bad arguments\n");
	free_split(texture_info);
	return (0);
}

int	parseWestTexture(char *line, t_map *map)
{
	char	**texture_info;
	int		count_info;
	int		existing_file;

	texture_info = ft_split(line, ' ');
	// texture_info[1] = ft_strtrim(texture_info[1], "\n");
	// ft_printf("WE Texture: %s\n", texture_info[1]);
	count_info = count_split_elements(texture_info);
	if (count_info == 2)
	{
		if (ft_strcmp(texture_info[0], "WE") == 0)
		{
			/* Function to check that files extension is .xpm */
			if (access(texture_info[1], F_OK) == 0)
			{
				map->we = ft_strdup(texture_info[1]);
				free_split(texture_info);
				// ft_printf("Success\n");
				return (1);
			}
			else
			{
				free_split(texture_info);
				// ft_printf("Texture not found\n");
				return(0);
			}
		}
	}
	// ft_printf("Bad arguments\n");
	free_split(texture_info);
	return (0);
}

int	parseNorthTexture(char *line, t_map *map)
{
	char	**texture_info;
	int		count_info;
	int		existing_file;

	texture_info = ft_split(line, ' ');
	// texture_info[1] = ft_strtrim(texture_info[1], "\n");
	// ft_printf("NO Texture: %s\n", texture_info[1]);
	count_info = count_split_elements(texture_info);
	if (count_info == 2)
	{
		if (ft_strcmp(texture_info[0], "NO") == 0)
		{
			/* Function to check that files extension is .xpm */
			if (access(texture_info[1], F_OK) == 0)
			{
				map->no = ft_strdup(texture_info[1]);
				free_split(texture_info);
				// ft_printf("Success\n");
				return (1);
			}
			else
			{
				free_split(texture_info);
				// ft_printf("Texture not found\n");
				return(0);
			}
		}
	}
	// ft_printf("Bad arguments\n");
	free_split(texture_info);
	return (0);
}

int	parseSouthTexture(char *line, t_map *map)
{
	char	**texture_info;
	int		count_info;
	int		existing_file;

	texture_info = ft_split(line, ' ');
	// texture_info[1] = ft_strtrim(texture_info[1], "\n");
	// ft_printf("SO Texture: %s\n", texture_info[1]);
	count_info = count_split_elements(texture_info);
	if (count_info == 2)
	{
		if (ft_strcmp(texture_info[0], "SO") == 0)
		{
			/* Function to check that files extension is .xpm */
			if (access(texture_info[1], F_OK) == 0)
			{
				map->so = ft_strdup(texture_info[1]);
				free_split(texture_info);
				// ft_printf("Success\n");
				return (1);
			}
			else
			{
				free_split(texture_info);
				// ft_printf("Texture not found\n");
				return(0);
			}
		}
	}
	// ft_printf("Bad arguments\n");
	free_split(texture_info);
	return (0);
}