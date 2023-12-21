/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:41:26 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/21 09:50:28 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_minimap(t_map *map, t_data *img)
{
	t_minimap_helper	helper;
	int					size;

	helper.start = (t_vector){.x = SCREEN_WIDTH / 2
		- (map->columns * MAP_SCALE) / 2, .y = 10};
	size = MAP_SCALE;
	helper.pos.x = -1;
	while (++helper.pos.x < map->rows)
	{
		helper.pos.y = -1;
		while (++helper.pos.y < map->columns)
		{
			if (map->map[(int) helper.pos.x][(int) helper.pos.y] == '1')
				draw_square_walls(helper.start.x, helper.start.y, size, img);
			else if (map->map[(int) helper.pos.x][(int) helper.pos.y] == 'D')
				draw_door(helper.start.x, helper.start.y, size, img);
			else if (map->map[(int) helper.pos.x][(int) helper.pos.y] == 'O')
				draw_open_door(helper.start.x, helper.start.y, size, img);
			else
				draw_square(helper.start.x, helper.start.y, size, img);
			helper.start.x += MAP_SCALE;
		}
		helper.start.x = SCREEN_WIDTH / 2 - (map->columns * MAP_SCALE) / 2;
		helper.start.y += MAP_SCALE;
	}
}

void	draw_player(t_map *map, t_data *img)
{
	t_view_params		params;
	t_vector			mapped;

	draw_intersections(map, img);
	mapped = map_vec_adjust(map->player_position, map);
	draw_disk(mapped.x, mapped.y, 3, img);
	params.fov_start = map_vec(rotate(map->direction, -FOV / 2), map);
	params.fov_end = map_vec(rotate(map->direction, FOV / 2), map);
	params.origin = map_vec_adjust(map->player_position, map);
	params.fov_start_endpoint = add(params.fov_start, params.origin);
	params.intersections = compute_intersections(map->player_position,
			params.fov_start, map);
	params.endpoint = params.intersections.points[params.intersections.size
		- 1];
	params.endpoint = map_vec_adjust(params.endpoint, map);
	draw_line(img, params.origin, params.endpoint, BLUE);
	params.intersections = compute_intersections(map->player_position,
			params.fov_end, map);
	params.endpoint = params.intersections.points[params.intersections.size
		- 1];
	params.endpoint = map_vec_adjust(params.endpoint, map);
	draw_line(img, params.origin, params.endpoint, BLUE);
}

void	draw_floor_ceiling(t_map *map, t_data *img)
{
	int	i;
	int	j;

	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		j = -1;
		while (++j < SCREEN_HEIGHT / 2)
		{
			my_mlx_pixel_put(img, i, j, encode_rgb(0, map->ceiling_r,
					map->ceiling_g, map->ceiling_b));
		}
	}
	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		j = SCREEN_HEIGHT / 2 - 1;
		while (++j < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(img, i, j, encode_rgb(0, map->floor_r,
					map->floor_g, map->floor_b));
		}
	}
}

int	get_texture_color(t_data *texture, int x, int y)
{
	int	color;

	color = *(int *)(texture->addr + (y * texture->line_length + x
				* (texture->bits_per_pixel / 8)));
	return (color);
}

void	set_juicy_params(t_view_params *params, t_vector endpoint,
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
