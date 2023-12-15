/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:26:10 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/15 23:48:20 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

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
	map->floor_r = -1;
	map->floor_g = -1;
	map->floor_b = -1;
	map->ceiling_r = -1;
	map->ceiling_g = -1;
	map->ceiling_b = -1;
	map->rows = 0;
	map->columns = 0;
	map->map_start_line = 0;
	map->map = NULL;
	map->copy = NULL;
	map->mouse_click = 0;
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
		while (map->map[i] != NULL)
		{
			free(map->map[i]);
			map->map[i] = NULL;
			i++;
		}
		free(map->map);
	}
}
