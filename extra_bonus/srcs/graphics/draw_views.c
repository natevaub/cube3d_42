/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_views.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:07:20 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/20 11:26:46 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_hand(t_map *map, t_data *img)
{
	t_vector	loop;
	t_vector	new_size;
	t_vector	offset;
	t_vector	others;

	others.x = 2;
	new_size.x = SCREEN_WIDTH / others.x;
	new_size.y = SCREEN_HEIGHT / others.x;
	offset.x = (SCREEN_WIDTH - new_size.x) / 2;
	offset.y = SCREEN_HEIGHT - new_size.y;
	loop.x = -1;
	while (++loop.x < new_size.x)
	{
		loop.y = -1;
		while (++loop.y < new_size.y)
		{
			others.y = get_texture_color(map->texture_fight[map->fight_index],
					loop.x * others.x, loop.y * others.x);
			if (others.y != -16777216)
				my_mlx_pixel_put(img, loop.x + offset.x, loop.y + offset.y,
					others.y);
		}
	}
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

void	set_view_params(t_view_params *params, t_map *map)
{
	params->start = add(map->player_position,
			rotate(map->direction, -FOV / 2.0));
	params->end = add(map->player_position, rotate(map->direction, FOV / 2.0));
	params->line = sub_vector(params->end, params->start);
	params->n_line = normalize(params->line);
	params->dx = norm(params->line) / SCREEN_WIDTH;
}

void	draw_view(t_map *map, t_data *img)
{
	t_view_params	*params;
	t_data			*texture ;
	int				i;

	texture = NULL;
	params = ft_gc_malloc(sizeof(t_view_params));
	if (!params)
		return ;
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
