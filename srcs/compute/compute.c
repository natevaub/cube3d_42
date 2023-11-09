/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:59:24 by nvaubien          #+#    #+#             */
/*   Updated: 2023/11/09 03:19:53 by nvaubien         ###   ########.fr       */
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
t_vector map_vec(t_vector v, t_mapping m)
{
	t_vector screen;
	screen.x = (v.x / m.from_width) * m.to_width;
	screen.y = (v.y / m.from_height) * m.to_height;
	return screen;
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
float norm(t_vector vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
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
t_vector normalize(t_vector vec)
{
	float n = norm(vec);
	return (t_vector){.x = vec.x / n, .y = vec.y / n};
}


t_intersections  compute_intersections(t_vector origin, t_vector direction, t_map *map)
{
	int n_intersections = 0;
	t_vector *dynamic_res = (t_vector *)malloc(sizeof(t_vector) * 1);
	//t_vector n_direction = normalize(direction);

	float xy = fabs(direction.x / direction.y);
	float yx = fabs(direction.y / direction.x);

	if (direction.x < 0)
	{
		xy *= -1;
	}
	if (direction.y < 0)
	{
		yx *= -1;
	}

	float x_diag_increment = norm((t_vector){.x = 1, .y = yx});
	float y_diag_increment = norm((t_vector){.x = 1, .y = xy});

	// cast origin to nearest square
	t_vector current_square = (t_vector){.x = floor(origin.x), .y = floor(origin.y)};
	t_vector current_origin = (t_vector){.x = origin.x, .y = origin.y};



	// while current square in inside the limits
	while (current_square.x >= 0 && current_square.x <= map->rows_width && current_square.y >= 0 && current_square.y <= map->rows_count)
	{
		printf("Current Square: %f, %f\n", current_square.x, current_square.y);
		printf("Current Origin: %f, %f\n", current_origin.x, current_origin.y);
		int next_x;
		if (direction.x > 0)
		{
			next_x = current_square.x + 1;
		}
		else
		{
			next_x = current_square.x - 1;
		}
		int next_y;
		if (direction.y > 0)
		{
			next_y = current_square.y + 1;
		}
		else
		{
			next_y = current_square.y - 1;
		}
		float len_x = fabs(next_x - current_origin.x);
		float len_y = fabs(next_y - current_origin.y);

		float diag_for_len_x = x_diag_increment * len_x;
		float diag_for_len_y = y_diag_increment * len_y;
		printf("Len x: %f\n", len_x);
		printf("Len y: %f\n", len_y);
		printf("x diag increment: %f\n", x_diag_increment);
		printf("y diag increment: %f\n", y_diag_increment);
		printf("Diag for len x: %f\n", diag_for_len_x);
		printf("Diag for len y: %f\n", diag_for_len_y);

		float new_origin_x;
		float new_origin_y;
		if (diag_for_len_x <= diag_for_len_y) {
			printf("X is smaller\n");
			current_square.x = next_x;
			new_origin_x = next_x;
			printf("New Origin X: %f\n", new_origin_x);
			new_origin_y = current_origin.y + yx * len_x;
			printf("yx: %f\n", yx);
			printf("New Origin Y: %f\n", new_origin_y);
		} 

		if (diag_for_len_y <= diag_for_len_x) {
			printf("Y is smaller\n");
			current_square.y = next_y;
			new_origin_y = next_y;
			printf("New Origin Y: %f\n", new_origin_y);
			new_origin_x = current_origin.x + xy * len_y;
			printf("xy: %f\n", xy);

			printf("New Origin X: %f\n", new_origin_x);
		}
		current_origin.x = new_origin_x;
		current_origin.y = new_origin_y;
		printf("\n");

		// Now check if dynamic res is full, if so realloc and add current origin inside
		if (n_intersections == 0)
		{
			dynamic_res[0] = current_origin;
		}
		else
		{
			t_vector *tmp = (t_vector *)malloc(sizeof(t_vector) * (n_intersections + 1));
			for (int i = 0; i < n_intersections; i++)
			{
				tmp[i] = dynamic_res[i];
			}
			tmp[n_intersections] = current_origin;
			free(dynamic_res);
			dynamic_res = tmp;
		}
		n_intersections += 1;
	}

	return (t_intersections){.size = n_intersections, .points = dynamic_res};
}

// int exemple(t_map map) {
// 	t_vector pos = (t_vector){.x = 4, .y = 4};
// 	t_vector dir = (t_vector){.x = 2, .y = 1};

// 	t_mapping mapping = {
// 		.from_width = map.rows_width,
// 		.from_height = map.rows_count,
// 		.to_width = map.rows_width * 20,
// 		.to_height = map.rows_count * 20};
// 	// Pretty print mapping
// 	printf("Mapping:\n");
// 	printf("From Width: %d\n", mapping.from_width);
// 	printf("From Height: %d\n", mapping.from_height);
// 	printf("To Width: %d\n", mapping.to_width);
// 	printf("To Height: %d\n", mapping.to_height);

// 	t_intersections intersections = compute_intersections(pos, dir, &map);
// 	for (int i = 0; i < intersections.size; i++)
// 	{
// 		printf("Intersection %d: %f, %f\n", i, intersections.points[i].x, intersections.points[i].y);
// 	}
// 	t_vector pp = (t_vector){.x = pos.x + dir.x, .y = pos.y + dir.y};
// }