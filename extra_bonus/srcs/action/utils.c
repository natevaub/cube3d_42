/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:41:22 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/21 09:31:25 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	handle_fight_mode(t_map *map)
{
	long		current_time;
	long		elapsed_time;
	int			new_index;

	current_time = get_current_time();
	elapsed_time = current_time - map->attack_start_time;
	new_index = elapsed_time / DELAY_THRESHOLD;
	if (new_index != map->fight_index)
	{
		map->fight_index = new_index;
		if (map->fight_index >= 4)
		{
			map->fight_index = 0;
			map->fight_mode = 0;
			map->sounds.type = NO_SOUND;
			map->sounds.playing = false;
		}
	}
}

int vectors_are_equal(t_vector vec1, t_vector vec2) {
    return (vec1.x == vec2.x) && (vec1.y == vec2.y);
}

void	render_and_display(t_map *map)
{
	t_vector	old_pos;
	t_data		new_image;

	old_pos = map->player_position;
	new_image.img = mlx_new_image(map->m_mlx.mlx_ptr, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	new_image.addr = mlx_get_data_addr(new_image.img, &new_image.bits_per_pixel,
			&new_image.line_length, &new_image.endian);
	mlx_clear_window(map->m_mlx.mlx_ptr, map->m_mlx.mlx_win);
	draw_view(map, &new_image);
	draw_minimap(map, &new_image);
	// draw_player(map, &new_image);
	if (!map->fight_mode)
	{
		// if (vectors_are_equal(old_pos, map->player_position))
			// map->sounds.type = SOUND_FART;
		draw_hand(map, &new_image);
	}
	else
	{
		draw_hand(map, &new_image);
		handle_fight_mode(map);
	}
	if (map->sounds.type && !map->sounds.playing)
	{
		sound_play(map->sounds.type);
		map->sounds.playing = true;
	}
	// if (fart_sound)
	// 	sound_play("sounds/farts/fart01.mp3");
	if (map->m_mlx.img.img)
		mlx_destroy_image(map->m_mlx.mlx_ptr, map->m_mlx.img.img);
	map->m_mlx.img = new_image;
	update_frame(map);
	map->frames++;
}
