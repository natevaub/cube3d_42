/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:46:43 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/19 12:49:46 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
			draw_wall_slice(texture, img, params->endpoint,
				params->beg, params->end);
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

void	set_view_params(t_view_params *params, t_map *map)
{
	params->start = add(map->player_position,
			rotate(map->direction, -FOV / 2.0));
	params->end = add(map->player_position, rotate(map->direction, FOV / 2.0));
	params->line = sub_vector(params->end, params->start);
	params->n_line = normalize(params->line);
	params->dx = norm(params->line) / SCREEN_WIDTH;
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