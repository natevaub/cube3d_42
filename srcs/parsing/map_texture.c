#include "../../includes/cube.h"

int	parseEastTexture(char *line, t_map *map)
{
	char	**texture_info;
	int		count_info;
	int		existing_file;

	texture_info = ft_split(line, ' ');
	ft_printf("EA Texture: %s\n", texture_info[1]);
	count_info = count_split_elements(texture_info);
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
	ft_printf("WE Texture: %s\n", texture_info[1]);
	count_info = count_split_elements(texture_info);
	if (count_info == 2)
	{
		if (ft_strcmp(texture_info[0], "WE") == 0)
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

int	parseNorthTexture(char *line, t_map *map)
{
	char	**texture_info;
	int		count_info;
	int		existing_file;

	texture_info = ft_split(line, ' ');
	ft_printf("NO Texture: %s\n", texture_info[1]);
	count_info = count_split_elements(texture_info);
	if (count_info == 2)
	{
		if (ft_strcmp(texture_info[0], "NO") == 0)
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

int	parseSouthTexture(char *line, t_map *map)
{
	char	**texture_info;
	int		count_info;
	int		existing_file;

	texture_info = ft_split(line, ' ');
	ft_printf("SO Texture: %s\n", texture_info[1]);
	count_info = count_split_elements(texture_info);
	if (count_info == 2)
	{
		if (ft_strcmp(texture_info[0], "SO") == 0)
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