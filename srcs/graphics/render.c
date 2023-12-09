/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:43:35 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/08 20:00:32 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cube.h"

// void	draw_intersections(t_map *map, t_data *img, t_mapping *mapping)
// {
// 	int				i;
// 	t_intersections	intersections;
// 	t_vector		v;
// 	// print v to see if it's correct

// 	v = map->direction;
// 	// printf("v: %f, %f\n", v.x, v.y);
// 	intersections = compute_intersections(map->player_position, v, map);
// 	i = 0;
// 	while (i < intersections.size)
// 	{
// 		t_vector mapped = map_vec(intersections.points[i], map->mapping);
// 		mapped.x += SCREEN_WIDTH / 2 - (map->columns * MAP_SCALE) / 2;
// 		mapped.y += 10;
// 		draw_disk(mapped.x, mapped.y, 3, img, RED);
// 		// printf("intersection %d: %f, %f\n", i, intersections.points[i].x, intersections.points[i].y);
// 		i++;
// 	}
// 	free(intersections.points);
// 	// draw_line(img, (t_vector){.x = 100, .y = 100}, (t_vector){.x = 300, .y = 300}, RED);
// }

void	draw_intersections(t_map *map, t_data *img, t_mapping *mapping)
{
	int				i;
	t_intersections	intersections;
	t_vector		v;
	// print v to see if it's correct

	v = map->direction;
	// printf("v: %f, %f\n", v.x, v.y);
	intersections = compute_intersections(map->player_position, v, map);
	i = 0;
	while (i < intersections.size)
	{
		t_vector mapped = map_vec_adjust(intersections.points[i], map);
		draw_disk(mapped.x, mapped.y, 3, img, RED);
		// printf("intersection %d: %f, %f\n", i, intersections.points[i].x, intersections.points[i].y);
		i++;
	}
	free(intersections.points);
	// draw_line(img, (t_vector){.x = 100, .y = 100}, (t_vector){.x = 300, .y = 300}, RED);
}

void update_frame(t_map *map)
{
	if (map->m_mlx.img.img) {
		mlx_put_image_to_window(map->m_mlx.mlx_ptr, map->m_mlx.mlx_win, map->m_mlx.img.img, 0, 0);
	} else {
		// Handle the case where the image pointer is NULL
		// fprintf(stderr, "Error: Invalid image pointer in update_frame\n");
	}
}

void	game_loop(t_map *map)
{

	map->frames = 0;
	map->start_time = (int)time(NULL);
	load_textures(map, &map->m_mlx);
	event_manager(map);
	// render_on_screen(m_mlx, map, mapping);
	// render_on_screen(map);
	mlx_loop_hook(map->m_mlx.mlx_ptr, game_loop_callback, map);
	mlx_loop(map->m_mlx.mlx_ptr);
	int current_time = (int)time(NULL);
}



int	game_loop_callback(t_map *map)
{
	t_data new_image;
	new_image.img = mlx_new_image(map->m_mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	new_image.addr = mlx_get_data_addr(new_image.img, &new_image.bits_per_pixel, &new_image.line_length, &new_image.endian);

	draw_view(map, &new_image, &map->mapping);
	draw_minimap(map, &new_image, &map->mapping);
	draw_player(map, &new_image, &map->mapping);
	// draw_square_text(map, &new_image, &map->mapping);
	

	// Destroy the previous image
	if (map->m_mlx.img.img)
	{
		mlx_destroy_image(map->m_mlx.mlx_ptr, map->m_mlx.img.img);
	}

	// Update the image pointer in the map
	map->m_mlx.img = new_image;

	// Call the update_frame function to display the new frame
	update_frame(map);
	int current_time = (int)time(NULL);
	map->frames++;
	float fps = (float)map->frames / (current_time - map->start_time);
	// printf("\033[2J\033[H");
	// printf("FPS: %f\n", fps);
	return (0);
}