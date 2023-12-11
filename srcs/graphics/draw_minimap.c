/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:41:26 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/11 17:25:22 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void draw_minimap(t_map *map, t_data *img, t_mapping *mapping)
{
	t_vector start;
	int size;
	int i;
	int j;

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

void draw_player(t_map *map, t_data *img, t_mapping *mapping)
{
	t_minimap_params params;
	t_vector mapped;

	draw_intersections(map, img, mapping);
	mapped = map_vec_adjust(map->player_position, map);
	draw_disk(mapped.x, mapped.y, 3, img, GREEN);
	params.FOV_start = map_vec(rotate(map->direction, -FOV / 2), map);
	params.FOV_end = map_vec(rotate(map->direction, FOV / 2), map);
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

void draw_floor_ceiling(t_map *map, t_data *img, t_mapping *mapping)
{
	int i;
	int j;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		j = 0;
		while (j < SCREEN_HEIGHT / 2)
		{
			my_mlx_pixel_put(img, i, j, encode_rgb(0, map->ceiling_R, map->ceiling_G, map->ceiling_B));
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
			my_mlx_pixel_put(img, i, j, encode_rgb(0, map->floor_R, map->floor_G, map->floor_B));
			j++;
		}
		i++;
	}
}

void load_textures(t_map *map, t_mlx *mlx)
{
	int size = 1024;

	map->texture_no = malloc(sizeof(t_data));
	map->texture_no->img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->no, &size, &size);
	map->texture_no->addr = mlx_get_data_addr(map->texture_no->img, &map->texture_no->bits_per_pixel, &map->texture_no->line_length, &map->texture_no->endian);
	map->texture_so = malloc(sizeof(t_data));
	map->texture_so->img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->so, &size, &size);
	map->texture_so->addr = mlx_get_data_addr(map->texture_so->img, &map->texture_so->bits_per_pixel, &map->texture_so->line_length, &map->texture_so->endian);
	map->texture_we = malloc(sizeof(t_data));
	map->texture_we->img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->we, &size, &size);
	map->texture_we->addr = mlx_get_data_addr(map->texture_we->img, &map->texture_we->bits_per_pixel, &map->texture_we->line_length, &map->texture_we->endian);
	map->texture_ea = malloc(sizeof(t_data));
	map->texture_ea->img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->ea, &size, &size);
	map->texture_ea->addr = mlx_get_data_addr(map->texture_ea->img, &map->texture_ea->bits_per_pixel, &map->texture_ea->line_length, &map->texture_ea->endian);
}

int get_texture_color(t_data *texture, int x, int y)
{
	int color;

	color = *(int *)(texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8)));
	return (color);
}

void draw_square_text(t_map *map, t_data *img, t_mapping *mapping)
{
	t_data *texture;

	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			my_mlx_pixel_put(img, i, j, CYAN);
		}
	}
	load_textures(map, &map->m_mlx);
	texture = map->texture_ea;
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			my_mlx_pixel_put(img, i, j, get_texture_color(texture, i, j));
		}
	}
}

void draw_view(t_map *map, t_data *img, t_mapping *mapping)
{
	draw_floor_ceiling(map, img, mapping);

	t_vector start = add(map->player_position, rotate(map->direction, -FOV / 2.0));
	t_vector end = add(map->player_position, rotate(map->direction, FOV / 2.0));
	t_vector line = sub_vector(end, start);
	t_vector n_line = normalize(line);
	t_data *texture;
	float dx = norm(line) / SCREEN_WIDTH;

	for (int i = 0; i < SCREEN_HEIGHT /* SCREEN_HEIGHT */; i++)
	{

		t_vector point = add(start, mul_scalar(n_line, dx * i));
		t_vector dir = normalize(sub_vector(point, map->player_position));

		t_intersections intersections = compute_intersections(map->player_position, dir, map);
		t_vector endpoint = intersections.points[intersections.size - 1];
		t_vector dist = sub_vector(endpoint, map->player_position);

		float perpDist = norm(dist) * cos(atan2(dir.y, dir.x) - atan2(map->direction.y, map->direction.x));
		float h = SCREEN_HEIGHT / perpDist;

		t_vector beg = (t_vector){.x = i, .y = SCREEN_HEIGHT / 2 - h / 2};
		t_vector end = (t_vector){.x = i, .y = SCREEN_HEIGHT / 2 + h / 2};
		t_vector n = sub_vector(end, beg);

		// clamp beg and end to 0, screen_height
		// if (beg.y < 0)
		// {
		// 	beg.y = 0;
		// }
		// if (end.y > SCREEN_HEIGHT)
		// {
		// 	end.y = SCREEN_HEIGHT;
		// }

		draw_juicy_line(img, map, endpoint, beg, end);

		free(intersections.points);
	}
}
