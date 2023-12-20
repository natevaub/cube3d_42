/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:43:35 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/20 15:22:12 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_intersections(t_map *map, t_data *img)
{
	int				i;
	t_intersections	intersections;
	t_vector		mapped;
	t_vector		v;

	v = map->direction;
	intersections = compute_intersections(map->player_position, v, map);
	i = -1;
	while (++i < intersections.size)
	{
		mapped = map_vec_adjust(intersections.points[i], map);
		draw_disk(mapped.x, mapped.y, 3, img);
	}
}

void	update_frame(t_map *map)
{
	if (map->m_mlx.img.img)
		mlx_put_image_to_window(map->m_mlx.mlx_ptr,
			map->m_mlx.mlx_win, map->m_mlx.img.img, 0, 0);
	else
		return ;
}

void	game_loop(t_map *map)
{
	map->frames = 0;
	map->start_time = (int)time(NULL);
	load_textures(map, &map->m_mlx);
	event_manager(map);
	mlx_loop_hook(map->m_mlx.mlx_ptr, game_loop_callback, map);
	mlx_loop(map->m_mlx.mlx_ptr);
}

int vectors_are_equal(t_vector vec1, t_vector vec2)
{
    return (vec1.x == vec2.x) && (vec1.y == vec2.y);
}

int	game_loop_callback(t_map *map)
{
	static int	first_play = 0;
	t_vector	old_pos;
	time_t		current_time = get_current_time();

	old_pos = map->player_position;
	render_and_display(map);
	if (vectors_are_equal(old_pos, map->player_position) && !map->fight_mode)
	{
		int	randnum = rand() % 10000;

		if ((current_time - map->last_position_change > randnum) && !first_play)
		{
			if (map->sounds.type == NO_SOUND)
			{
				map->sounds.type = SOUND_FART;
				sound_play(map->sounds.type);
			}
			else if (map->sounds.type == SOUND_FART && current_time - map->last_position_change > randnum + 500)
			{
				first_play = 1;
				map->sounds.type = SOUND_VOICE;
				sound_play(map->sounds.type);
			}
		}
	}
	else
	{
		map->last_position_change = current_time;
		map->sounds.type = NO_SOUND;
	}
	return (0);
}
