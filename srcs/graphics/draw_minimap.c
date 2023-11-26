/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:41:26 by nvaubien          #+#    #+#             */
/*   Updated: 2023/11/26 02:40:53 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	draw_non_walls(t_map *map, t_data *img, t_mapping *mapping)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->rows_count)
	{
		while (j < map->rows_width)
		{
			if (map->map[i][j] == '0')
			{
				draw_square(j * mapping->to_width, i * mapping->to_height,
					mapping->to_width, img);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_minimap(t_map *map, t_data *img, t_mapping *mapping)
{
	t_vector	start;
	int			size;
	int			i;
	int			j;

	start = (t_vector){.x = SCREEN_WIDTH / 2 - (map->rows_width * MAP_SCALE) / 2, .y = 10};
	size = MAP_SCALE;
	i = 0;
	while (i < map->rows_count)
	{
		j = 0;
		while (j < map->rows_width)
		{
			if (map->map[i][j] == '1')
				draw_square_walls(start.x, start.y, size, img);
			else
				draw_square(start.x, start.y, size, img);
			start.x += MAP_SCALE;
			j++;
		}
		i++;
		start.x = SCREEN_WIDTH / 2 - (map->rows_width * MAP_SCALE) / 2;
		j = 0;
		start.y += MAP_SCALE;
	}
}

void	draw_player(t_map *map, t_data *img, t_mapping *mapping)
{
	t_vector	mapped = map_vec(map->player_position, *mapping);

	mapped.x += SCREEN_WIDTH / 2 - (map->rows_width * MAP_SCALE) / 2;
	mapped.y += 10;
	// printf("mapped player position: %f, %f\n", mapped.x, mapped.y);
	draw_disk(mapped.x, mapped.y, 3, img, GREEN);
	t_vector fov_start = map_vec(rotate(map->direction, -60 / 2), map->mapping);
	t_vector fov_end = map_vec(rotate(map->direction, 60 / 2), map->mapping);

	t_vector origin = map_vec(map->player_position, map->mapping);
	origin.x = origin.x + SCREEN_WIDTH / 2 - (map->rows_width * MAP_SCALE) / 2;
	origin.y = origin.y + 10;
	t_vector fov_start_endpoint = add(fov_start, origin);
	t_vector fov_end_endpoint = add(fov_end, origin);

	t_intersections	intersections;

	intersections = compute_intersections(map->player_position, fov_start, map);
	t_vector endpoint = intersections.points[intersections.size - 1];
	endpoint = map_vec(endpoint, map->mapping);
	endpoint.x = endpoint.x + SCREEN_WIDTH / 2 - (map->rows_width * MAP_SCALE) / 2;
	endpoint.y = endpoint.y + 10;
	draw_line(img, origin, endpoint, BLUE);

	intersections = compute_intersections(map->player_position, fov_end, map);
	endpoint = intersections.points[intersections.size - 1];
	endpoint = map_vec(endpoint, map->mapping);
	endpoint.x = endpoint.x + SCREEN_WIDTH / 2 - (map->rows_width * MAP_SCALE) / 2;
	endpoint.y = endpoint.y + 10;
	draw_line(img, origin, endpoint, BLUE);
}

void	draw_view(t_map *map, t_data *img, t_mapping *mapping)
{
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		for (int j = 0; j < SCREEN_HEIGHT; j++) {
			if (j < SCREEN_WIDTH / 2)
			{
				my_mlx_pixel_put(img, i, j, encode_rgb(map->ceiling_R, map->ceiling_G, map->ceiling_B, 0));
			}
			else
			{
				my_mlx_pixel_put(img, i, j, encode_rgb(map->floor_R, map->floor_G, map->floor_B, 0));
			}
		}
	}

	float fov = 60;

	

	t_vector start = add(map->player_position, rotate(map->direction, -fov / 2.0));
	t_vector end = add(map->player_position, rotate(map->direction, fov / 2.0));

	t_vector line = sub_scalar(end, start);
	t_vector n_line = normalize(line);

	float dx = norm(line) / SCREEN_WIDTH;


	
	for (int i = 0; i < SCREEN_WIDTH; i++) {

		t_vector point = add(start, mul_scalar(n_line, dx * i));
		t_vector dir = normalize(sub_scalar(point, map->player_position));


		t_intersections intersections = compute_intersections(map->player_position, dir, map);
		// printf("player position: %d %f, %f\n",i,  map->player_position.x, map->player_position.y);
		t_vector endpoint = intersections.points[intersections.size - 1];
		t_vector dist = sub_scalar(endpoint, map->player_position);
		// printf("endpoint: %f, %f\n", endpoint.x, endpoint.y);
		float angle = -fov + (120.0 / SCREEN_WIDTH) * i;
		float n_dist = norm(dist);
		float scale_fac = 1.0 / n_dist;
		// printf("scale_fac: %f dist: %f\n", scale_fac, n_dist);


		float l = SCREEN_HEIGHT - (scale_fac * SCREEN_HEIGHT) / 2;

		t_vector beg = (t_vector){.x = i, .y = l};
		t_vector end = (t_vector){.x = i, .y = SCREEN_HEIGHT - l};

		// t_vector beg = (t_vector){.x = i, .y = 100};
		// t_vector end = (t_vector){.x = i, .y = SCREEN_HEIGHT - 100};

		t_vector n = sub_scalar(end, beg);
		printf("n: %f, %f, scale_fac: %f, n_dist: %f, i: %d. angle: %f\n", n.x, n.y, scale_fac, n_dist, i, angle);
		// print current
		// printf("current: %f, %f\n", current.x, current.y);


		if (endpoint.y == (int)endpoint.y) {
			draw_line(img, beg, end, RED);
		}
		if (endpoint.x == (int)endpoint.x) {
			draw_line(img, beg, end, GREEN);
		}
		

		free(intersections.points);
	}

}