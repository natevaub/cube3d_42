/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:00:28 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/16 00:33:28 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

int	map_transform_to_parsable(t_map *map)
{
	int	i;

	i = 0;
	map->map = (char **)ft_calloc(sizeof(char *), (map->rows + 1));
	if (map->map == NULL)
		return (5);
	map->map[map->rows] = NULL;
	while (i < map->rows)
	{
		if (!contains_only_valid(map->copy[map->map_start_line]))
		{
			return (6);
		}
		map->map[i] = fill_map(map->copy[map->map_start_line], map);
		i++;
		map->map_start_line++;
	}
	return (0);
}

int	map_check_hole(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	debug_print_map(map);
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (i > 0 && i < map->rows - 1 && j > 0 && j < map->columns - 1)
			{
				if (map->map[i][j] == '0' || map->map[i][j] == 'N'
					|| map->map[i][j] == 'S'
					|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
				{
					if (map->map[i][j + 1] == '2' || map->map[i][j - 1] == '2'
						|| map->map[i + 1][j] == '2'
						|| map->map[i - 1][j] == '2')
						return (1);
				}
			}
		}
	}
	return (0);
}

int	map_transform_to_usable(t_map *map)
{
	int	i;
	int	j;

	if (map_check_hole(map))
		return (7);
	i = 0;
	j = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == '2')
			{
				map->map[i][j] = '1';
			}
			j++;
		}
		i++;
	}
	if (!is_valid_map(map))
		return (8);
	return (0);
}
