/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 23:38:43 by nvaubien          #+#    #+#             */
/*   Updated: 2023/11/21 22:04:34 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

t_intersections	compute_intersections(t_vector or, t_vector dir, t_map *map)
{
	t_compute	*c;

	c = (t_compute *)malloc(sizeof(t_compute));
	c->dynamic_res = (t_vector *)malloc(sizeof(t_vector));
	initialize_compute(or, dir, c);
	while (c->curr_square.x >= 0 && c->curr_square.x <= map->rows_width
		&& c->curr_square.y >= 0 && c->curr_square.y <= map->rows_count)
	{
		if (check_collision(map, c))
			break ;
		update_next_x_and_y(or, dir, c);
		update_compute_state(c);
		if (c->curr_origin.x >= 0 && c->curr_origin.x <= map->rows_width
			&& c->curr_origin.y >= 0 && c->curr_origin.y <= map->rows_count)
		{
			store_intersections(c);
		}
	}
	return ((t_intersections){.size = c->n_inter, .points = c->dynamic_res});
}

void	store_intersections(t_compute *c)
{
	int	i;

	i = 0;
	if (c->n_inter == 0)
		c->dynamic_res[0] = c->curr_origin;
	else
	{
		c->tmp = (t_vector *)malloc(sizeof(t_vector) * (c->n_inter + 1));
		i = 0;
		while (i < c->n_inter)
		{
			c->tmp[i] = c->dynamic_res[i];
			i++;
		}
		c->tmp[c->n_inter] = c->curr_origin;
		free(c->dynamic_res);
		c->dynamic_res = c->tmp;
	}
	c->n_inter += 1;
}

int	check_collision(t_map *map, t_compute *c)
{
	c->eps = 0.0001;
	c->test = add(c->curr_origin, mul_scalar(c->n_direction, c->eps));
	c->x = map->map[(int)c->test.y][(int)c->test.x];
	if (c->x == '1')
		return (1);
	return (0);
}



void	test_inter(t_map *map, t_mapping *mapping, t_test *test)
{
	test->pos = *map->player_position;
	test->dir = (t_vector){.x = 2, .y =-1.5};

	test->intersections = compute_intersections(test->pos, test->dir, map);
	for (int i = 0; i < test->intersections.size; i++)
	{
		printf("Intersection %d: %f, %f, %c\n", i, test->intersections.points[i].x, test->intersections.points[i].y,
			map->map[(int)test->intersections.points[i].y][(int)test->intersections.points[i].x]
		);
	}
	test->pp = (t_vector){.x = test->pos.x + test->dir.x, .y = test->pos.y + test->dir.y};
}
