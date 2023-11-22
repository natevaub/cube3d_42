#include "../includes/cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(int x, int y, int size, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i == size - 1 || i == 0 || j == size - 1 || j == 0)
			{
				my_mlx_pixel_put(img, x + i, y + j, WHITE);
			}
			else
			{
				my_mlx_pixel_put(img, x + i, y + j, LIGHT_GRAY);
			}
			j++;
		}
		i++;
	}
}

void	draw_square_walls(int x, int y, int size, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i == size - 1 || i == 0 || j == size - 1 || j == 0)
			{
				my_mlx_pixel_put(img, x + i, y + j, WHITE);
			}
			else
			{
				my_mlx_pixel_put(img, x + i, y + j, DARK_GRAY);
			}
			j++;
		}
		i++;
	}
}

void draw_line(t_data *img, t_vector start, t_vector end, int color)
{
	float x;
	float y;
	float dx;
	float dy;
	float step;
	float i;

	dx = end.x - start.x;
	dy = end.y - start.y;
	step = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
	dx /= step;
	dy /= step;
	x = start.x;
	y = start.y;
	i = 0;
	while (i <= step)
	{
		if (x < 0 || x >= img->line_length || y < 0 || y >= img->line_length) {
		i++;
			continue;

		}
		my_mlx_pixel_put(img, x, y, color);
		x += dx;
		y += dy;
		i++;
	}
}

void draw_disk(int x, int y, int radius, t_data *img, int color)
{
	for (int i = x - radius; i <= x + radius; i++) {
		for (int j = y - radius; j <= y + radius; j++) {
			if (i < 0 || i >= img->line_length || j < 0 || j >= img->line_length)
				continue;
			int dx = i - x;
			int dy = j - y;
			if (dx * dx + dy * dy <= radius * radius) {
				my_mlx_pixel_put(img, i, j, color);
			}
		}
	}
}

void minimap_square(t_map *map, t_data *img, t_intersections intersections, t_vector pos, t_vector dir, t_mapping *mapping)
{
	ft_printf("Map Row Width %d\n", map->rows_width);
	ft_printf("Map Row Count %d\n", map->rows_count);
	int	size = 50;
	ft_printf("Square Width %d\n", size);
	int	x, y;
	int	i, j;

	y = 0; x = 0;
	i = 0; j = 0;

	while (i < map->rows_count)
	{
		while (j < map->rows_width)
		{
			if (map->map[i][j] == '1')
			{
				draw_square_walls(x, y, size, img);
			}
			else
			{
				draw_square(x, y, size, img);
			}
			x += size;
			j++;
		}
		i++;
		x = 0;
		j = 0;
		y += size;
	}

	for (int i = 0; i < intersections.size; i++)
	{
		t_vector mapped = map_vec(intersections.points[i], *mapping);
		draw_disk(mapped.x, mapped.y, 3, img, RED);
	}
	t_vector start = pos;
	t_vector end = add(pos, map_vec(normalize(dir), *mapping) );
	// normalized dir
	t_vector normed_dir = normalize(dir);

	printf("Pos: %f, %f\n", pos.x, pos.y);
	printf("Start: %f, %f\n", start.x, start.y);
	// print normalized dir
	printf("Dir: %f, %f\n", normed_dir.x, normed_dir.y);
	printf("End: %f, %f\n\n", end.x, end.y);

	// draw_line(img, start, end, RED);
	// draw a line from player position to last intersection
	// draw_line(img, pos, intersections.points[intersections.size - 1], RED);
	// previous line doesn't work I think you should map_vec
	draw_line(img, pos, map_vec(intersections.points[intersections.size - 1], *mapping), RED);
}

void	draw_player(t_map *map, t_data *img, t_mapping *mapping)
{
	t_vector	mapped = map_vec(*map->player_position, *mapping);
	draw_disk(mapped.x, mapped.y, 3, img, GREEN);

}

int	encode_rgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}