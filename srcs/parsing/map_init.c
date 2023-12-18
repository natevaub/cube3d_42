/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:26:10 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/18 18:29:35 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_ceiling_floor(t_map *map)
{
	map->floor_r = -1;
	map->floor_g = -1;
	map->floor_b = -1;
	map->ceiling_r = -1;
	map->ceiling_g = -1;
	map->ceiling_b = -1;
}

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
	map->rows = 0;
	map->columns = 0;
	map->map_start_line = 0;
	map->map = NULL;
	map->copy = NULL;
	map->fight_index = 0;
	map->fight_mode = 0;
	map->fight_mode_counter = 0;
	map->attackStartTime = 0;
	map->door = 0;
	map->speed = SPEED;
	init_ceiling_floor(map);
}
