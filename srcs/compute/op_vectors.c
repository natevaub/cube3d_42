/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:34:24 by nvaubien          #+#    #+#             */
/*   Updated: 2023/11/25 23:32:57 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

/**
 * map_vec - Maps a vector from one coordinate system to another.
 *
 * This function takes a vector 'v' and a mapping 'm' and maps the vector
 * from one coordinate system defined by 'from_width' and 'from_height' to
 * another coordinate system defined by 'to_width' and 'to_height'. The
 * resulting mapped vector is returned.
 *
 * @param v The input vector to be mapped.
 * @param m The mapping parameters specifying the coordinate conversion.
 * @return The mapped vector in the new coordinate system.
*/
t_vector	map_vec(t_vector v, t_mapping m)
{
	t_vector	screen;

	screen.x = (v.x / m.from_width) * m.to_width;
	screen.y = (v.y / m.from_height) * m.to_height;
	return (screen);
}

/**
 * norm - Calculates the Euclidean norm (magnitude) of a vector.
 *
 * This function computes the Euclidean norm of a given vector 'vec', which
 * represents the magnitude or length of the vector.
 *
 * @param vec The input vector for which the norm is to be calculated.
 * @return The Euclidean norm (magnitude) of the input vector.
*/
float	norm(t_vector vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

/**
 * normalize - Normalizes a vector to unit length.
 *
 * This function normalizes a given vector 'vec' by dividing its components
 * by its Euclidean norm, resulting in a unit vector (a vector with length 1).
 *
 * @param vec The vector to be normalized.
 * @return The normalized unit vector.
 */
t_vector	normalize(t_vector vec)
{
	float	n;

	n = norm(vec);
	return ((t_vector){.x = vec.x / n, .y = vec.y / n});
}

t_vector	add(t_vector a, t_vector b)
{
	return ((t_vector){.x = a.x + b.x, .y = a.y + b.y});
}

t_vector	sub_scalar(t_vector a, t_vector b)
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
	return (v);
}

t_vector rotate(t_vector v, float degrees) {
	float radians = degrees * 3.14 / 180;
	float cos = cosf(radians);
	float sin = sinf(radians);
	return (t_vector){.x = v.x * cos - v.y * sin, .y = v.x * sin + v.y * cos};
}