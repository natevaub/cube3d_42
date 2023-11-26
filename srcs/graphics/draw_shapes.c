#include "../includes/cube.h"

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
