/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:26:10 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/20 14:14:47 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_others(t_map *map)
{
	map->floor_r = -1;
	map->floor_g = -1;
	map->floor_b = -1;
	map->ceiling_r = -1;
	map->ceiling_g = -1;
	map->ceiling_b = -1;
	map->ct_door = 0;
	map->mouse_view = 0;
	map->last_position_change = get_current_time();
}

t_sounds	init_sounds(void)
{
    t_sounds new_sound;

    new_sound.path = NULL;
    new_sound.pid = -1;
    new_sound.played = false;
    new_sound.playing = false;
    new_sound.type = NO_SOUND;
    return (new_sound);
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
	map->attack_start_time = 0;
	map->speed = SPEED;
	map->sounds = init_sounds();
	init_others(map);
}
