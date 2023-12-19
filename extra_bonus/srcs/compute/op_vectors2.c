/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vectors2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:21:46 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/19 11:21:49 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_vector	add(t_vector a, t_vector b)
{
	return ((t_vector){.x = a.x + b.x, .y = a.y + b.y});
}

t_vector	sub_vector(t_vector a, t_vector b)
{
	return ((t_vector){.x = a.x - b.x, .y = a.y - b.y});
}

t_vector	add_scalar(t_vector a, float b)
{
	return ((t_vector){.x = a.x + b, .y = a.y + b});
}

t_vector	mul_scalar(t_vector a, float b)
{
	return ((t_vector){.x = a.x * b, .y = a.y * b});
}

t_vector	transform_pdirection_to_vector(char direction)
{
	t_vector	v;

	if (direction == 'N')
		v = (t_vector){.x = 0, .y = -1};
	else if (direction == 'S')
		v = (t_vector){.x = 0, .y = 1};
	else if (direction == 'E')
		v = (t_vector){.x = 1, .y = 0};
	else if (direction == 'W')
		v = (t_vector){.x = -1, .y = 0};
	else
		v = (t_vector){.x = 0, .y = 0};
	return (v);
}
