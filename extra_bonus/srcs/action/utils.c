/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:41:22 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/19 19:09:12 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	handle_fight_mode(t_map *map, t_data *new_image)
{
	long	current_time;
	long	elapsed_time;
	int		new_index;
	int		punch_sound;

	punch_sound = 0;
	current_time = get_current_time();
	elapsed_time = current_time - map->attack_start_time;
	new_index = elapsed_time / DELAY_THRESHOLD;
	if (new_index != map->fight_index)
	{
		if (new_index == 1)
			punch_sound = 1;
		map->fight_index = new_index;
		if (map->fight_index >= 4)
		{
			map->fight_index = 0;
			map->fight_mode = 0;
			punch_sound = 0;
		}
		else
		{
			mlx_clear_window(map->m_mlx.mlx_ptr, map->m_mlx.mlx_win);
			draw_view(map, new_image);
			draw_minimap(map, new_image);
			draw_player(map, new_image);
			draw_hand(map, new_image);
		}
	}
	return (punch_sound);
}

void	render_and_display(t_map *map)
{
	t_data	new_image;
	int		punch_sound;

	punch_sound = 0;
	new_image.img = mlx_new_image(map->m_mlx.mlx_ptr, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	new_image.addr = mlx_get_data_addr(new_image.img, &new_image.bits_per_pixel,
			&new_image.line_length, &new_image.endian);
	draw_view(map, &new_image);
	draw_minimap(map, &new_image);
	draw_player(map, &new_image);
	if (!map->fight_mode)
		draw_hand(map, &new_image);
	else
		punch_sound = handle_fight_mode(map, &new_image);
	plays_sounds(punch_sound);
	if (map->m_mlx.img.img)
		mlx_destroy_image(map->m_mlx.mlx_ptr, map->m_mlx.img.img);
	map->m_mlx.img = new_image;
	update_frame(map);
	map->frames++;
}
