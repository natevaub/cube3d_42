/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:59:24 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/16 14:23:30 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_mapping(t_map *map, t_mapping *mapping)
{
	mapping->from_width = map->columns;
	mapping->from_height = map->rows;
	mapping->to_width = map->columns * MAP_SCALE;
	mapping->to_height = map->rows * MAP_SCALE;
}

void	initialize_compute(t_vector or, t_vector dir, t_compute *compute)
{
	t_vector	tmp;

	compute->n_direction = normalize(dir);
	compute->xy = fabs(dir.x / dir.y);
	compute->yx = fabs(dir.y / dir.x);
	if (dir.x < 0)
		compute->xy *= -1;
	if (dir.y < 0)
		compute->yx *= -1;
	tmp.x = 1;
	tmp.y = compute->yx;
	compute->x_diag_increment = norm(tmp);
	tmp.y = compute->xy;
	compute->y_diag_increment = norm(tmp);
	compute->curr_square = (t_vector){.x = floor(or.x), .y = floor(or.y)};
	compute->curr_origin = (t_vector){.x = or.x, .y = or.y};
}

void	update_next_x_and_y(t_vector or, t_vector dir, t_compute *c)
{
	(void)or;
	if (dir.x > 0)
		c->next_x = floor(c->curr_origin.x + 1);
	else
		c->next_x = ceil(c->curr_origin.x - 1);
	if (dir.y > 0)
		c->next_y = floor(c->curr_origin.y + 1);
	else
		c->next_y = ceil(c->curr_origin.y - 1);
}

void	update_compute_state(t_compute *c)
{
	c->len_x = fabs(c->next_x - c->curr_origin.x);
	c->len_y = fabs(c->next_y - c->curr_origin.y);
	c->diag_for_len_x = c->x_diag_increment * c->len_x;
	c->diag_for_len_y = c->y_diag_increment * c->len_y;
	if (c->diag_for_len_x <= c->diag_for_len_y)
	{
		c->new_origin_x = c->next_x;
		c->new_origin_y = c->curr_origin.y + c->yx * c->len_x;
	}
	if (c->diag_for_len_y <= c->diag_for_len_x)
	{
		c->new_origin_y = c->next_y;
		c->new_origin_x = c->curr_origin.x + c->xy * c->len_y;
	}
	c->curr_origin.x = c->new_origin_x;
	c->curr_origin.y = c->new_origin_y;
}
