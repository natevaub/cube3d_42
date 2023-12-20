/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 23:38:43 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/20 11:26:37 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_intersections	compute_intersections(t_vector or, t_vector dir, t_map *map)
{
	t_compute	*c;
	t_vector	*dynamic_res;
	int			n_inter;

	n_inter = 0;
	c = (t_compute *)ft_gc_malloc(sizeof(t_compute));
	dynamic_res = (t_vector *)ft_gc_malloc(sizeof(t_vector));
	if (!c || !dynamic_res)
		return ((t_intersections){.size = 0, .points = NULL});
	initialize_compute(or, dir, c);
	while ((int)c->curr_origin.x >= 0 && (int)c->curr_origin.x <= map->columns
		&& (int)c->curr_origin.y >= 0 && (int)c->curr_origin.y <= map->rows)
	{
		if (check_collision(map, c))
			break ;
		update_next_x_and_y(or, dir, c);
		update_compute_state(c);
		if (c->curr_origin.x >= 0 && c->curr_origin.x <= map->columns
			&& c->curr_origin.y >= 0 && c->curr_origin.y <= map->rows)
		{
			store_intersections(c, &n_inter, &dynamic_res);
		}
	}
	return ((t_intersections){.size = n_inter, .points = dynamic_res});
}

void	store_intersections(t_compute *c, int *n_inter, t_vector **dynamic_res)
{
	int	i;

	i = 0;
	if (*n_inter == 0)
		(*dynamic_res)[0] = c->curr_origin;
	else
	{
		c->tmp = (t_vector *)ft_gc_malloc(sizeof(t_vector) * (*n_inter + 1));
		if (!c->tmp)
			return ;
		i = 0;
		while (i < *n_inter)
		{
			c->tmp[i] = (*dynamic_res)[i];
			i++;
		}
		c->tmp[*n_inter] = c->curr_origin;
		*dynamic_res = c->tmp;
	}
	*n_inter += 1;
}

int	check_collision(t_map *map, t_compute *c)
{
	c->eps = 0.0001;
	c->test = add(c->curr_origin, mul_scalar(c->n_direction, c->eps));
	c->x = map->map[(int)c->test.y][(int)c->test.x];
	if (c->x == '1' || c->x == 'D')
		return (1);
	return (0);
}
