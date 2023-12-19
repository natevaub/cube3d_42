/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:00:23 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/19 18:47:07 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	helper_valid_ceiling_color(char **ceilingValues, t_map *map)
{
	int	value;
	int	i;

	i = 0;
	while (ceilingValues[i] != NULL)
	{
		value = ft_atoi(ceilingValues[i]);
		if (value < 0 || value > 255)
		{
			return (0);
		}
		if (i == 0)
			map->ceiling_r = value;
		else if (i == 1)
			map->ceiling_g = value;
		else if (i == 2)
			map->ceiling_b = value;
		i++;
	}
	return (1);
}

int	helper_valid_floor_color(char **floorValues, t_map *map)
{
	int	value;
	int	i;

	i = 0;
	while (floorValues[i] != NULL)
	{
		value = ft_atoi(floorValues[i]);
		if (value < 0 || value > 255)
		{
			return (0);
		}
		if (i == 0)
			map->floor_r = value;
		else if (i == 1)
			map->floor_g = value;
		else if (i == 2)
			map->floor_b = value;
		i++;
	}
	return (1);
}

void	parse_elements(char *line, t_map *map)
{
	parse_east_texture(line, map);
	parse_west_texture(line, map);
	parse_north_texture(line, map);
	parse_south_texture(line, map);
	parse_floor(line, map);
	parse_ceiling(line, map);
	parse_door_texture(line, map);
}

int	map_start(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if ((line[i] && line[i] == '1'))
		return (1);
	return (0);
}

char	*fill_map(char *line, t_map *map)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = ft_calloc(map->columns + 1, sizeof(char));
	if (new_line == NULL)
		return (NULL);
	if (line[i])
	{
		while (line[i] && j < map->columns)
		{
			if (line[i] == ' ')
				new_line[j] = '1';
			else
				new_line[j] = line[i];
			i++;
			j++;
		}
	}
	while (j < map->columns)
		new_line[j++] = '2';
	new_line[j] = '\0';
	return (new_line);
}
