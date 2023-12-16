/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:43:35 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/16 19:02:19 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void draw_intersections(t_map *map, t_data *img)
{
	int i;
	t_intersections intersections;
	t_vector v;

	v = map->direction;
	intersections = compute_intersections(map->player_position, v, map);
	i = 0;
	while (i < intersections.size)
	{
		t_vector mapped = map_vec_adjust(intersections.points[i], map);
		draw_disk(mapped.x, mapped.y, 3, img, RED);
		i++;
	}
}

void update_frame(t_map *map)
{
	if (map->m_mlx.img.img)
		mlx_put_image_to_window(map->m_mlx.mlx_ptr, map->m_mlx.mlx_win, map->m_mlx.img.img, 0, 0);
	else
	{
		// Handle the case where the image pointer is NULL
		// fprintf(stderr, "Error: Invalid image pointer in update_frame\n");
	}
}

void game_loop(t_map *map)
{
	map->frames = 0;
	map->start_time = (int)time(NULL);
	load_textures(map, &map->m_mlx);
	event_manager(map);
	mlx_loop_hook(map->m_mlx.mlx_ptr, game_loop_callback, map);
	mlx_loop(map->m_mlx.mlx_ptr);
}
void	attack(t_map *map);

int game_loop_callback(t_map *map)
{
	t_data new_image;
	new_image.img = mlx_new_image(map->m_mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	new_image.addr = mlx_get_data_addr(new_image.img, &new_image.bits_per_pixel, &new_image.line_length, &new_image.endian);

	draw_view(map, &new_image);
	draw_hand(map, &new_image);
	draw_minimap(map, &new_image);
	draw_player(map, &new_image);
	if (map->m_mlx.img.img)
		mlx_destroy_image(map->m_mlx.mlx_ptr, map->m_mlx.img.img);
	map->m_mlx.img = new_image;
	if (map->fight_mode == 1)
	{
		attack(map);
	}
	update_frame(map);
	map->frames++;
	return (0);
}