/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:41:26 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/21 09:37:55 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// int main(void)
// {
//     void *mlx_ptr;
//     void *win_ptr;
//     int width = 400;
//     int height = 300;

//     mlx_ptr = mlx_init();
//     win_ptr = mlx_new_window(mlx_ptr, width, height, "New Image");
//     void *img = mlx_new_image(mlx_ptr, width, height);
//     int *data = (int *)mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);

//     for(int y = 0; y < height; y++)
//     {
//         for(int x = 0; x < width; x++)
//         {
//             // Let's draw a red pixel at each (x, y)
//             data[y * width + x] = 0xFF0000;
//         }
//     }

//     mlx_put_image_to_window(mlx_ptr, win_ptr, img, 0, 0);
//     mlx_loop(mlx_ptr);

//     return (0);
// }

void draw_minimap(t_map *map, t_data *img)
{
	// t_vector start;
	// int size;
	// int i;
	// int j;

	// void *img = mlx_new_image(map->m_mlx.mlx_ptr, 300, 300);
	// int *data = (int *)mlx_get_data_addr(img, map->m_mlx.img.bits_per_pixel, map->m_mlx.img.line_length, map->m_mlx.img.endian);
	// map->

	(void)img;
	// # Make miimap red
	for (int y = 0; y < MINIMAP_HEIGHT; y++)
	{
		for (int x = 0; x < MINIMAP_WIDTH; x++)
		{
			// Let's draw a red pixel at each (x, y)
			// data[y * MINIMAP_WIDTH + x] = 0xFF0000;
			my_mlx_pixel_put(&map->m_mlx.minimap, x, y, 0x000000);
		}
	}

	// int square_size = 5;

	float player_x = map->player_position.x;
	float player_y = map->player_position.y;
	int minimap_half_viewport = MAP_SCALE;
	float start_x = player_x - minimap_half_viewport;
	float end_x = player_x + minimap_half_viewport;
	float start_y = player_y - minimap_half_viewport;
	float end_y = player_y + minimap_half_viewport;

	float scale_x = (end_x - start_x) / MINIMAP_WIDTH;
	float scale_y = (end_y - start_y) / MINIMAP_HEIGHT;

	// draw the minimap, if a pixel position in the map is 1, draw a block else draw nothing

	for (int i = 0; i < MINIMAP_WIDTH; i++)
	{
		for (int j = 0; j < MINIMAP_HEIGHT; j++)
		{

			// convert to map space based on the user position, the user position is the center of the minimap
			float xx = i * scale_x + start_x;
			float yy = j * scale_y + start_y;

			int xxx = (int)(xx);
			int yyy = (int)(yy);

			// if point outside of map, skip
			if (xxx < 0 || xxx >= map->columns || yyy < 0 || yyy >= map->rows)
				continue;

			// printf("xx: %f, yy: %f, xxx: %d, yyy: %d\n", xx, yy, xxx, yyy);

			// if point is inside of map, draw a block
			if (map->map[yyy][xxx] == '1')
				my_mlx_pixel_put(&map->m_mlx.minimap, i, j, 0xFF0000);
			else
				my_mlx_pixel_put(&map->m_mlx.minimap, i, j, 0x00FF00);

			// draw border, if epsilon close to an edge of a square in the map, draw a border
			if (xx - (int)xx < 0.1 || xx - (int)xx > 0.9 || yy - (int)yy < 0.1 || yy - (int)yy > 0.9)
				my_mlx_pixel_put(&map->m_mlx.minimap, i, j, 0x0000FF);

			// float map_x = player_x

			// 	if (map->map[i][j] == '1')
			// {
			// 	// draw a block
			// 	// data[y * MINIMAP_WIDTH + x] = 0xFF0000;
			// 	my_mlx_pixel_put(&map->m_mlx.minimap, i, j, 0xFF0000);
			// }
		}
	}

	// Draw the player at the center of the minimap with a disk
	draw_disk(MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2, 7, &map->m_mlx.minimap);
	t_vector direction = normalize(map->direction);
	t_vector middle_position = (t_vector){.x = MINIMAP_WIDTH / 2, .y = MINIMAP_HEIGHT / 2};
	t_vector endpoint = add(middle_position, mul_scalar(direction, 20));

	draw_line(&map->m_mlx.minimap, middle_position, endpoint, 0x0000FF);
}

void draw_player(t_map *map, t_data *img)
{
	t_view_params params;
	t_vector mapped;

	draw_intersections(map, img);
	mapped = map_vec_adjust(map->player_position, map);
	draw_disk(mapped.x, mapped.y, 3, img);
	params.fov_start = map_vec(rotate(map->direction, -FOV / 2), map);
	params.fov_end = map_vec(rotate(map->direction, FOV / 2), map);
	params.origin = map_vec_adjust(map->player_position, map);
	params.fov_start_endpoint = add(params.fov_start, params.origin);
	params.intersections = compute_intersections(map->player_position,
												 params.fov_start, map);
	params.endpoint = params.intersections.points[params.intersections.size - 1];
	params.endpoint = map_vec_adjust(params.endpoint, map);
	draw_line(img, params.origin, params.endpoint, BLUE);
	params.intersections = compute_intersections(map->player_position,
												 params.fov_end, map);
	params.endpoint = params.intersections.points[params.intersections.size - 1];
	params.endpoint = map_vec_adjust(params.endpoint, map);
	draw_line(img, params.origin, params.endpoint, BLUE);
}

void draw_floor_ceiling(t_map *map, t_data *img)
{
	int i;
	int j;

	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		j = -1;
		while (++j < SCREEN_HEIGHT / 2)
			my_mlx_pixel_put(img, i, j, encode_rgb(0, map->ceiling_r, map->ceiling_g, map->ceiling_b));
	}
	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		j = SCREEN_HEIGHT / 2 - 1;
		while (++j < SCREEN_HEIGHT)
			my_mlx_pixel_put(img, i, j, encode_rgb(0, map->floor_r, map->floor_g, map->floor_b));
	}
}

int get_texture_color(t_data *texture, int x, int y)
{
	int color;

	color = *(int *)(texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8)));
	return (color);
}

void set_juicy_params(t_view_params *params, t_vector endpoint,
					  t_vector start, t_vector end)
{
	params->x = endpoint.x - floor(endpoint.x);
	params->y = endpoint.y - floor(endpoint.y);
	if (params->x == 0)
		params->variant = params->y;
	if (params->y == 0)
		params->variant = params->x;
	params->texture_col = (int)floor(params->variant * 1024);
	params->step = end.y - start.y;
	params->dy = params->step / params->step;
}
