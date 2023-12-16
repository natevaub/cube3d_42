/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:34:24 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/16 17:58:22 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
t_vector	map_vec(t_vector v, t_map *m)
{
	t_vector	screen;

	screen.x = (v.x / m->mapping.from_width) * m->mapping.to_width;
	screen.y = (v.y / m->mapping.from_height) * m->mapping.to_height;
	return (screen);
}

t_vector map_vec_adjust(t_vector v, t_map *m)
{
    t_vector screen;

    screen.x = SCREEN_WIDTH / 2 + (v.x - m->player_position.x) * MAP_SCALE;
    screen.y = SCREEN_HEIGHT / 2 + (v.y - m->player_position.y) * MAP_SCALE;
	screen.y -= 450;
	screen.x += 5;
    return screen;
}

// t_vector	map_vec_adjust(t_vector v, t_map *m)
// {
// 	t_vector	screen;

// 	screen.x = (v.x / m->mapping.from_width) * m->mapping.to_width;
// 	screen.y = (v.y / m->mapping.from_height) * m->mapping.to_height;
// 	screen.x += SCREEN_WIDTH / 2 - (m->columns * MAP_SCALE) / 2;
// 	screen.y += 10;
// 	return (screen);
// }

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

t_vector	rotate(t_vector v, float degrees)
{
	float	radians;
	float	cos;
	float	sin;

	radians = degrees * M_PI / 180;
	cos = cosf(radians);
	sin = sinf(radians);
	return ((t_vector){.x = v.x * cos - v.y * sin, .y = v.x * sin + v.y * cos});
}
