/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:41:26 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/19 18:07:52 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_door(int x, int y, int size, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i == size - 1 || i == 0 || j == size - 1 || j == 0)
				my_mlx_pixel_put(img, x + i, y + j, WHITE);
			else
				my_mlx_pixel_put(img, x + i, y + j, BROWN);
			j++;
		}
		i++;
	}
}

void	draw_open_door(int x, int y, int size, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i == size - 1 || i == 0 || j == size - 1 || j == 0)
				my_mlx_pixel_put(img, x + i, y + j, WHITE);
			else
				my_mlx_pixel_put(img, x + i, y + j, GREEN);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_map *map, t_data *img)
{
	t_vector	start;
	int			size;
	int			i;
	int			j;

	start = (t_vector){.x = SCREEN_WIDTH / 2 - (map->columns * MAP_SCALE) / 2,
		.y = 10};
	size = MAP_SCALE;
	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->columns)
		{
			if (map->map[i][j] == '1')
				draw_square_walls(start.x, start.y, size, img);
			else if (map->map[i][j] == 'D')
				draw_door(start.x, start.y, size, img);
			else if (map->map[i][j] == 'O')
				draw_open_door(start.x, start.y, size, img);
			else
				draw_square(start.x, start.y, size, img);
			start.x += MAP_SCALE;
		}
		start.x = SCREEN_WIDTH / 2 - (map->columns * MAP_SCALE) / 2;
		start.y += MAP_SCALE;
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

void	set_view_params(t_view_params *params, t_map *map)
{
	params->start = add(map->player_position,
			rotate(map->direction, -FOV / 2.0));
	params->end = add(map->player_position, rotate(map->direction, FOV / 2.0));
	params->line = sub_vector(params->end, params->start);
	params->n_line = normalize(params->line);
	params->dx = norm(params->line) / SCREEN_WIDTH;
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

void	update_view_params(t_map *map, t_view_params *params, int *i)
{
	params->point = add(params->start,
			mul_scalar(params->n_line, params->dx * *i));
	params->dir = normalize(sub_vector(params->point,
				map->player_position));
	params->intersections = compute_intersections(map->player_position,
			params->dir, map);
	params->endpoint = params->intersections.points
	[params->intersections.size - 1];
	params->dist = sub_vector(params->endpoint, map->player_position);
	params->perp_dist = norm(params->dist)
		* cos(atan2(params->dir.y, params->dir.x)
			- atan2(map->direction.y, map->direction.x));
	params->h = SCREEN_HEIGHT / params->perp_dist;
	params->beg = (t_vector){.x = *i, .y = SCREEN_HEIGHT / 2 - params->h / 2};
	params->end = (t_vector){.x = *i, .y = SCREEN_HEIGHT / 2 + params->h / 2};
}

void	assign_texture_view(t_map *map, t_view_params *params, t_data **texture)
{
	char	cell;

	cell = map->map[(int)params->endpoint.y][(int)params->endpoint.x];
	if (cell == 'D')
		*texture = map->texture_door;
	else if (params->endpoint.y == (int)params->endpoint.y)
	{
		if (map->player_position.y > params->endpoint.y)
			*texture = map->texture_no;
		else
			*texture = map->texture_so;
	}
	else if (params->endpoint.x == (int)params->endpoint.x)
	{
		if (map->player_position.x > params->endpoint.x)
			*texture = map->texture_we;
		else
			*texture = map->texture_ea;
	}
}

void	draw_view(t_map *map, t_data *img)
{
	t_view_params	*params;
	t_data			*texture ;
	int				i;

	texture = NULL;
	params = ft_gc_malloc(sizeof(t_view_params));
	draw_floor_ceiling(map, img);
	set_view_params(params, map);
	i = -1;
	while (++i < SCREEN_HEIGHT)
	{
		update_view_params(map, params, &i);
		assign_texture_view(map, params, &texture);
		if (texture)
			draw_wall_slice(texture, img, params);
	}
}

// void	draw_hand(t_map *map, t_data *img)
// {
// 	t_vector	loop;
// 	t_vector	new_size;
// 	t_vector	offset;
// 	t_vector	others;

// 	others.x = 2;
// 	new_size.x = SCREEN_WIDTH / others.x;
// 	new_size.y = SCREEN_HEIGHT / others.x;
// 	offset.x = (SCREEN_WIDTH - new_size.x) / 2;
// 	offset.y = SCREEN_HEIGHT - new_size.y;
// 	loop.x = -1;
// 	while (++loop.x < new_size.x)
// 	{
// 		loop.y = -1;
// 		while (++loop.y < new_size.y)
// 		{
// 			others.y = get_texture_color(map->texture_fight[map->fight_index],
// 					loop.x * others.x, loop.y * others.x);
// 			if (others.y != -16777216)
// 				my_mlx_pixel_put(img, loop.x + offset.x, loop.y + offset.y,
// 					others.y);
// 		}
// 	}
// }
