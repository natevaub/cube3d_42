// t_intersections compute_intersections(t_vector origin, t_vector direction, t_map *map)
// {
// 	// print direction
// 	// printf("Direction: %f, %f\n", direction.x, direction.y);
// 	// printf("Origin: %f, %f\n", origin.x, origin.y);
// 	int n_inter = 0;
// 	t_vector *dynamic_res = (t_vector *)malloc(sizeof(t_vector) * 1);
// 	t_vector n_direction = normalize(direction);

// 	float xy = fabs(direction.x / direction.y);
// 	// printf("XY: %f\n", xy);
// 	float yx = fabs(direction.y / direction.x);
// 	// printf("YX: %f\n", yx);

// 	if (direction.x < 0)
// 	{
// 		xy *= -1;
// 	}
// 	if (direction.y < 0)
// 	{
// 		yx *= -1;
// 	}

// 	float x_diag_increment = norm((t_vector){.x = 1, .y = yx});
// 	float y_diag_increment = norm((t_vector){.x = 1, .y = xy});
// 	// printf("X diag increment: %f\n", x_diag_increment);
// 	// printf("Y diag increment: %f\n", y_diag_increment);


// 	// cast origin to nearest square
// 	// t_vector curr_square = (t_vector){.x = floor(origin.x), .y = floor(origin.y)};
// 	t_vector current_origin = (t_vector){.x = origin.x, .y = origin.y};



// 	// while current square in inside the limits
// 	// while (intcurrent_origin.x >= 0 && curr_square.x <= map->columns && curr_square.y >= 0 && curr_square.y <= map->rows)
// 	while ((int)current_origin.x >=0 && (int)current_origin.x <= map->columns && (int)current_origin.y >= 0 && (int)current_origin.y <= map->rows)
// 	{
// 		t_vector curr_square = (t_vector){.x = floor(current_origin.x), .y = floor(current_origin.y)};
// 		float eps = 0.0001;
// 		t_vector  t = add(current_origin, mul_scalar(n_direction, eps));
// 		char x = map->map[(int)t.y][(int)t.x];
// 		// printf("Current Square: %f, %f\n", curr_square.x, curr_square.y);
// 		// printf("Current Origin: %f, %f\n", current_origin.x, current_origin.y);
// 		// printf("Current Origin: %d, %d\n", (int)current_origin.x, (int)current_origin.y);
// 		// printf("T: %f, %f\n", t.x, t.y);
// 		// printf("t: %d, %d\n", (int)t.x, (int)t.y);
// 		// printf("X: %c\n\n", x);
// 		if (x == '1')
// 		{
// 			break;
// 		};
		

// 		// printf("Current Square: %f, %f\n", curr_square.x, curr_square.y);
// 		// printf("Current Origin: %f, %f\n", current_origin.x, current_origin.y);
// 		int next_x;
// 		if (direction.x > 0)
// 		{
// 			next_x = floor(current_origin.x + 1);
// 		}
// 		else
// 		{
// 			next_x = ceil(current_origin.x - 1);
// 		}
// 		int next_y;
// 		if (direction.y > 0)
// 		{
// 			next_y = floor(current_origin.y + 1);
// 		}
// 		else
// 		{
// 			next_y = ceil(current_origin.y - 1);
// 		}
// 		// printf("Next x Next y: %d %f, %d %f\n", next_x, curr_square.x, next_y, curr_square.y);
// 		float len_x = fabs(next_x - current_origin.x);
// 		float len_y = fabs(next_y - current_origin.y);

// 		float diag_for_len_x = x_diag_increment * len_x;
// 		float diag_for_len_y = y_diag_increment * len_y;
// 		// printf("Len x: %f\n", len_x);
// 		// printf("Len y: %f\n", len_y);
// 		// printf("Diag for len x: %f\n", diag_for_len_x);
// 		// printf("Diag for len y: %f\n", diag_for_len_y);
// 		// printf("xy: %f\n", xy);
// 		// printf("yx: %f\n", yx);

// 		float new_origin_x;
// 		float new_origin_y;
// 		if (diag_for_len_x <= diag_for_len_y) {
// 			// printf("X is smaller\n");
// 			new_origin_x = next_x;
// 			// printf("New Origin X: %f\n", new_origin_x);
// 			new_origin_y = current_origin.y + yx * len_x;
// 			// printf("yx: %f\n", yx);
// 			// printf("New Origin Y: %f\n", new_origin_y);
// 		} 

// 		else if (diag_for_len_y <= diag_for_len_x) {
// 			// printf("Y is smaller\n");
// 			new_origin_y = next_y;
// 			// printf("New Origin Y: %f\n", new_origin_y);
// 			new_origin_x = current_origin.x + xy * len_y;
// 			// printf("xy: %f\n", xy);

// 			// printf("New Origin X: %f\n", new_origin_x);
// 		}
// 		current_origin.x = new_origin_x;
// 		current_origin.y = new_origin_y;
// 		// printf("\n");

		

// 		// Now check if dynamic res is full, if so realloc and add current origin inside
// 		if (current_origin.x >= 0 && current_origin.x <= map->columns && current_origin.y >= 0 && current_origin.y <= map->rows)
// 		{
// 			if (n_inter == 0)
// 			{
// 				dynamic_res[0] = current_origin;
// 			}
// 			else
// 			{
// 				t_vector *tmp = (t_vector *)malloc(sizeof(t_vector) * (n_inter + 1));
// 				for (int i = 0; i < n_inter; i++)
// 				{
// 					tmp[i] = dynamic_res[i];
// 				}
// 				tmp[n_inter] = current_origin;
// 				free(dynamic_res);
// 				dynamic_res = tmp;
// 			}
		
// 			n_inter += 1;
// 			// printf("N inter: %d\n", n_inter);
// 		}
// 	}
// 	return (t_intersections){.size = n_inter, .points = dynamic_res};
// }