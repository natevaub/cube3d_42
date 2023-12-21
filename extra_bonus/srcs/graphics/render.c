/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:43:35 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/21 09:35:35 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void draw_intersections(t_map *map, t_data *img)
{
	int i;
	t_intersections intersections;
	t_vector mapped;
	t_vector v;

	v = map->direction;
	intersections = compute_intersections(map->player_position, v, map);
	i = -1;
	while (++i < intersections.size)
	{
		mapped = map_vec_adjust(intersections.points[i], map);
		draw_disk(mapped.x, mapped.y, 3, img);
	}
}

void update_frame(t_map *map)
{
	if (map->m_mlx.img.img)
	{
		printf("main\n");
		mlx_put_image_to_window(map->m_mlx.mlx_ptr,
								map->m_mlx.mlx_win, map->m_mlx.img.img, 0, 0);
	}

	printf("Minimap img: %p\n", map->m_mlx.minimap.img);
	if (map->m_mlx.minimap.img)
	{
		printf("minimap\n");
		mlx_put_image_to_window(map->m_mlx.mlx_ptr,
								map->m_mlx.mlx_win, map->m_mlx.minimap.img, 10, 10);
	}
	else
		return;
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

int game_loop_callback(t_map *map)
{
	render_and_display(map);
	return (0);
}
