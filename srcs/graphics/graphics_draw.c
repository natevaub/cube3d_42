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
            int dx = i - x;
            int dy = j - y;
            if (dx * dx + dy * dy <= radius * radius) {
                my_mlx_pixel_put(img, i, j, color);
            }
        }
    }
}

void minimap_square(t_map *map, t_data *img, t_intersections intersections, t_vector pos, t_vector dir)
{
	ft_printf("Map Row Width %d\n", map->rows_width);
	ft_printf("Map Row Count %d\n", map->rows_count);
	int	size = 20;
	ft_printf("Square Width %d\n", size);
	int	x, y;
	int	i, j;

	y = 0; x = 0;
	i = 0; j = 0;

	t_mapping mapping = {
		.from_width = map->rows_width,
		.from_height = map->rows_count,
		.to_width = map->rows_width * 20,
		.to_height = map->rows_count * 20};


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

	for  (int i = 0; i < intersections.size - 4; i++)
	{
		t_vector mapped = map_vec(intersections.points[i], mapping);
		draw_disk(mapped.x, mapped.y, 5, img, RED);
	}

	
	draw_line(img, pos, dir, RED);
}