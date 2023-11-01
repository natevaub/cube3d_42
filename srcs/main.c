#include "../includes/cube.h"

void debug_print_int_values(char *str)
{
	if (!str)
	{
		return;
	}
	for (int i = 0; i < ft_strlen(str); i++)
	{
		ft_printf("%d ", str[i]);
	}
	ft_printf("\n");
}

void debug_print_map(const t_map *map)
{
	printf("East Texture: %s\n", map->ea ? map->ea : "Not defined");
	printf("North Texture: %s\n", map->no ? map->no : "Not defined");
	printf("South Texture: %s\n", map->so ? map->so : "Not defined");
	printf("West Texture: %s\n", map->we ? map->we : "Not defined");

	printf("Floor Color: ");
	if (map->floor_R >= 0 && map->floor_G >= 0 && map->floor_B >= 0)
	{
		printf("%d,%d,%d\n", map->floor_R, map->floor_G, map->floor_B);
	}
	else
	{
		printf("Not defined\n");
	}

	printf("Ceiling Color: ");
	if (map->ceiling_R >= 0 && map->ceiling_G >= 0 && map->ceiling_B >= 0)
	{
		printf("%d,%d,%d\n", map->ceiling_R, map->ceiling_G, map->ceiling_B);
	}
	else
	{
		printf("Not defined\n");
	}

	printf("Texture Counts:\n");
	printf("East Texture Count: %d\n", map->count_ea);
	printf("North Texture Count: %d\n", map->count_no);
	printf("South Texture Count: %d\n", map->count_so);
	printf("West Texture Count: %d\n", map->count_we);

	printf("Ceiling Count: %d\n", map->count_ceiling);
	printf("Floor Count: %d\n", map->count_floor);

	printf("Rows Count: %d\n", map->rows_count);
	printf("Rows Width: %d\n", map->rows_width);
	printf("Map Copy:\n");
	printf("Map Content:\n");
	if (map->copy)
	{
		for (int i = 0; map->copy[i]; i++)
		{
			printf("%s\n", map->copy[i]);
		}
	}
	else
	{
		printf("Not defined\n");
	}

	printf("Map Content:\n");
	if (map->map)
	{
		for (int i = 0; map->map[i]; i++)
		{
			printf("%s\n", map->map[i]);
		}
	}
	else
	{
		printf("Not defined\n");
	}
}

void init_map(t_map *map, char **av)
{
	map->path = ft_strdup(av[1]);
	map->so = NULL;
	map->no = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->count_no = 0;
	map->count_ea = 0;
	map->count_so = 0;
	map->count_we = 0;
	map->count_floor = 0;
	map->count_ceiling = 0;
	map->floor_R = -1;
	map->floor_G = -1;
	map->floor_B = -1;
	map->ceiling_R = -1;
	map->ceiling_G = -1;
	map->ceiling_B = -1;
	map->rows_count = 0;
	map->rows_width = 0;
	map->map_start_line = 0;
	map->map = NULL;
	map->copy = NULL;
}

void free_map(t_map *map)
{
	int i;

	free(map->path);
	if (map->copy)
	{
		free_split(map->copy);
		free(map->so);
		free(map->no);
		free(map->we);
		free(map->ea);
	}
	if (map->map)
	{
		i = 0;
		while (map->map[i])
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
}

t_vector map_vec(t_vector v, t_mapping m)
{
	t_vector screen;
	screen.x = (v.x / m.from_width) * m.to_width;
	screen.y = (v.y / m.from_height) * m.to_height;
	return screen;
}

float norm(t_vector vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

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

int main(int ac, char **av)
{
	t_map map;
	int code_error;

	init_map(&map, av);
	// open_cub_file(map.path, &map);
	code_error = parser(&map);
	if (code_error)
		ft_printf("😔 Why are you doing this to me ? 😔\n");
	else if (!code_error)
		ft_printf("🔥 I'm ready to cast rayzzzz 🔥\n");
	// debug_print_map(&map);

	/* Je fais ma sauce */
	t_mlx graphics;
	graphics.img = (t_data *)malloc(sizeof(t_data));

	graphics.mlx = mlx_init();
	graphics.mlx_win = mlx_new_window(graphics.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
	graphics.img->img = mlx_new_image(graphics.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	/*
	** After creating an image, we can call `mlx_get_data_addr`, we pass
	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
	** then be set accordingly for the *current* data address.
	*/
	graphics.img->addr = mlx_get_data_addr(graphics.img->img, &graphics.img->bits_per_pixel, &graphics.img->line_length,
										   &graphics.img->endian);
	// draw_square(10, 20, 50, &img);

	t_vector pos = (t_vector){.x = 4, .y = 4};
	t_vector dir = (t_vector){.x = 2, .y = 1};

	t_mapping mapping = {
		.from_width = map.rows_width,
		.from_height = map.rows_count,
		.to_width = map.rows_width * 20,
		.to_height = map.rows_count * 20};
	// Pretty print mapping
	printf("Mapping:\n");
	printf("From Width: %d\n", mapping.from_width);
	printf("From Height: %d\n", mapping.from_height);
	printf("To Width: %d\n", mapping.to_width);
	printf("To Height: %d\n", mapping.to_height);

	t_intersections intersections = compute_intersections(pos, dir, &map);
	for (int i = 0; i < intersections.size; i++)
	{
		printf("Intersection %d: %f, %f\n", i, intersections.points[i].x, intersections.points[i].y);
	}


	t_vector pp = (t_vector){.x = pos.x + dir.x, .y = pos.y + dir.y};
	minimap_square(&map, graphics.img, intersections, map_vec(pos, mapping), map_vec(pp, mapping));
	// minimap_square(&map, &img);
	mlx_put_image_to_window(graphics.mlx, graphics.mlx_win, graphics.img->img, 0, 0);
	mlx_loop(graphics.mlx);

	/* Memory Management */
	free_map(&map);
	return (0);
}