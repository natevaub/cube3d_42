/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:43:35 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/19 13:31:56 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_intersections(t_map *map, t_data *img)
{
	int				i;
	t_intersections	intersections;
	t_vector		v;
	t_vector		mapped;

	v = map->direction;
	intersections = compute_intersections(map->player_position, v, map);
	i = 0;
	while (i < intersections.size)
	{
		mapped = map_vec_adjust(intersections.points[i], map);
		draw_disk(mapped.x, mapped.y, 3, img, RED);
		i++;
	}
}

void	update_frame(t_map *map)
{
	if (map->m_mlx.img.img)
		mlx_put_image_to_window(map->m_mlx.mlx_ptr,
			map->m_mlx.mlx_win, map->m_mlx.img.img, 0, 0);
	else
	{
		return ;
	}
}

void	game_loop(t_map *map)
{
	map->frames = 0;
	map->start_time = (int)time(NULL);
	load_textures_1(map, &map->m_mlx);
	load_textures_2(map, &map->m_mlx);
	event_manager(map);
	mlx_loop_hook(map->m_mlx.mlx_ptr, game_loop_callback, map);
	mlx_loop(map->m_mlx.mlx_ptr);
}

int	game_loop_callback(t_map *map)
{
	t_data	new_image;

	new_image.img = mlx_new_image(map->m_mlx.mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	new_image.addr = mlx_get_data_addr(new_image.img, &new_image.bits_per_pixel,
			&new_image.line_length, &new_image.endian);
	draw_view(map, &new_image);
	if (map->m_mlx.img.img)
		mlx_destroy_image(map->m_mlx.mlx_ptr, map->m_mlx.img.img);
	map->m_mlx.img = new_image;
	update_frame(map);
	map->frames++;
	return (0);
}
