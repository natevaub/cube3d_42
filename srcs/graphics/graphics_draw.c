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

void	minimap_square(t_map *map, t_data *img)
{
	ft_printf("Map Row Width %d\n", map->rows_width);
	ft_printf("Map Row Count %d\n", map->rows_count);
	int	size = (MINIMAP_WIDTH / map->rows_width);
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
}