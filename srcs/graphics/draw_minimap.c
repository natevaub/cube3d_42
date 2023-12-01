/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:41:26 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/01 00:07:29 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	draw_minimap(t_map *map, t_data *img, t_mapping *mapping)
{
	t_vector	start;
	int			size;
	int			i;
	int			j;

	start = (t_vector){.x = SCREEN_WIDTH / 2 - (map->columns * MAP_SCALE) / 2, .y = 10};
	size = MAP_SCALE;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->columns)
		{
			if (map->map[i][j] == '1')
				draw_square_walls(start.x, start.y, size, img);
			else
				draw_square(start.x, start.y, size, img);
			start.x += MAP_SCALE;
			j++;
		}
		i++;
		start.x = SCREEN_WIDTH / 2 - (map->columns * MAP_SCALE) / 2;
		j = 0;
		start.y += MAP_SCALE;
	}
}

void	draw_player(t_map *map, t_data *img, t_mapping *mapping)
{
	t_minimap_params 	params;
	t_vector			mapped;

	draw_intersections(map, img, mapping);
	mapped = map_vec_adjust(map->player_position, map);
	draw_disk(mapped.x, mapped.y, 3, img, GREEN);
	params.FOV_start = map_vec(rotate(map->direction, -45 / 2), map);
	params.FOV_end = map_vec(rotate(map->direction, 45 / 2), map);
	params.origin = map_vec_adjust(map->player_position, map);
	params.FOV_start_endpoint = add(params.FOV_start, params.origin);
	params.intersections = compute_intersections(map->player_position, params.FOV_start, map);
	params.endpoint = params.intersections.points[params.intersections.size - 1];
	params.endpoint = map_vec_adjust(params.endpoint, map);
	draw_line(img, params.origin, params.endpoint, BLUE);
	free(params.intersections.points);
	params.intersections = compute_intersections(map->player_position, params.FOV_end, map);
	params.endpoint = params.intersections.points[params.intersections.size - 1];
	params.endpoint = map_vec_adjust(params.endpoint, map);
	draw_line(img, params.origin, params.endpoint, BLUE);
	free(params.intersections.points);
}

void	draw_floor_ceiling(t_map *map, t_data *img, t_mapping *mapping)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		j = 0;
		while (j < SCREEN_HEIGHT / 2)
		{
			my_mlx_pixel_put(img, i, j, encode_rgb(map->ceiling_R, map->ceiling_G, map->ceiling_B, 0));
			j++;
		}
		i++;
	}
	i = 0;
	while (i < SCREEN_WIDTH)
	{
		j = SCREEN_HEIGHT / 2;
		while (j < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(img, i, j, encode_rgb(map->floor_R, map->floor_G, map->floor_B, 0));
			j++;
		}
		i++;
	}
}

void	draw_view(t_map *map, t_data *img, t_mapping *mapping)
{
	draw_floor_ceiling(map, img, mapping);

	t_vector start = add(map->player_position, rotate(map->direction, -FOV / 2.0));
	t_vector end = add(map->player_position, rotate(map->direction, FOV / 2.0));

	t_vector line = sub_vector(end, start);
	t_vector n_line = normalize(line);

	float dx = norm(line) / SCREEN_WIDTH;


	
	for (int i = 0; i < SCREEN_WIDTH; i++) {

		t_vector point = add(start, mul_scalar(n_line, dx * i));
		t_vector dir = normalize(sub_vector(point, map->player_position));


		t_intersections intersections = compute_intersections(map->player_position, dir, map);
		// printf("player position: %d %f, %f\n",i,  map->player_position.x, map->player_position.y);
		t_vector endpoint = intersections.points[intersections.size - 1];
		t_vector dist = sub_vector(endpoint, map->player_position);
		// printf("endpoint: %f, %f\n", endpoint.x, endpoint.y);
		float angle = -(FOV / 2) + (FOV / SCREEN_WIDTH) * i;
		float n_dist = norm(dist);
		float scale_fac = 1.0 / n_dist;
		// printf("scale_fac: %f dist: %f\n", scale_fac, n_dist);
		
		float h = 100 / (n_dist * 0.8);


		// float l = SCREEN_HEIGHT - (scale_fac * SCREEN_HEIGHT) / 2;

		t_vector beg = (t_vector){.x = i, .y = SCREEN_HEIGHT / 2 - h / 2};
		t_vector end = (t_vector){.x = i, .y = SCREEN_HEIGHT / 2 + h / 2};
		// printf("beg: %f, %f, end: %f, %f, dist: %f\n", beg.x, beg.y, end.x, end.y, n_dist);

		// t_vector beg = (t_vector){.x = i, .y = 100};
		// t_vector end = (t_vector){.x = i, .y = SCREEN_HEIGHT - 100};

		t_vector n = sub_vector(end, beg);
		// printf("n: %f, %f, scale_fac: %f, n_dist: %f, i: %d. angle: %f\n", n.x, n.y, scale_fac, n_dist, i, angle);
		// print current
		// printf("current: %f, %f\n", current.x, current.y);

		// clamp beg and end to 0, screen_height
		if (beg.y < 0) {
			beg.y = 0;
		}
		if (end.y > SCREEN_HEIGHT) {
			end.y = SCREEN_HEIGHT;
		}



		if (endpoint.y == (int)endpoint.y) {

			int m = (int)endpoint.y % 3;
			if (m == 0) {
				draw_line(img, beg, end, BLUE);
			} else if (m == 1) {
				draw_line(img, beg, end, RED);
			} else {
				draw_line(img, beg, end, GREEN);
			}
		}
		if (endpoint.x == (int)endpoint.x) {
			int m = (int)endpoint.x % 3;

			if (m == 0) {
				draw_line(img, beg, end, LIGHT_GRAY);
			} else if (m == 1) {
				draw_line(img, beg, end, DARK_GRAY);
			} else {
				draw_line(img, beg, end, 0);
			}	

		}
		
		free(intersections.points);
	}
}