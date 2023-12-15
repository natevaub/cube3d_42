#include "../includes/cube.h"

void draw_square(int x, int y, int size, t_data *img)
{
	int i;
	int j;

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

void draw_square_walls(int x, int y, int size, t_data *img)
{
	int i;
	int j;

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
	float step;
	float dx;
	float dy;
	float i;

	step = fmaxf(fabs(end.x - start.x), fabs(end.y - start.y));
	dx = (end.x - start.x) / step;
	dy = (end.y - start.y) / step;
	i = 0;
	while (i <= step)
	{
		start.x += dx;
		start.y += dy;
		if (start.x < 0 || start.x >= img->line_length || start.y < 0 || start.y >= img->line_length)
		{
			continue;
		}
		my_mlx_pixel_put(img, start.x, start.y, color);
		i++;
	}
}

// void draw_juicy_line(t_data *img, t_map *map, t_vector endpoint, t_vector start, t_vector end)
// {

// 	float x = endpoint.x - floor(endpoint.x);

// 	float y = endpoint.y - floor(endpoint.y);

// 	t_data *texture;
// 	float variant;
// 	if (x == 0)
// 	{
// 		variant = y;
// 		if ((int)endpoint.y % 2 == 0)
// 		{
// 			texture = map->texture_so;
// 		}
// 		else
// 		{
// 			texture = map->texture_no;
// 		}
// 	}
// 	if (y == 0)
// 	{
// 		variant = x;
// 		if ((int)endpoint.x % 2 == 0)
// 		{
// 			texture = map->texture_so;
// 		}
// 		else
// 		{
// 			texture = map->texture_no;
// 		}
// 	}

// 	int u = (int)(floor(x + y)) % 2;

// 	int texture_col = (int)floor(variant * 1024);

// 	float step;
// 	float dx;
// 	float dy;
// 	float i;

// 	// start.y -100 end.y 1124
// 	// step 1224
// 	// dy = 1
// 	// while 1 < 1224

// 	step = end.y - start.y;
// 	// end, start
// 	dy = step / step;
// 	i = 0;
// 	while (i <= step)
// 	{
// 		start.y += dy;

// 		if (start.x < 0 || start.x >= img->line_length || start.y < 0 || start.y >= img->line_length)
// 		{
// 			i++;
// 			continue;
// 		}

// 		int texture_row = i * 1023.0 / step;
// 		// int texture_row = (int)(i * 1023) / 1024;
// 		int color = get_texture_color(texture, texture_col, texture_row);
// 		my_mlx_pixel_put(img, start.x, start.y, color);
// 		i++;
// 	}
// 	printf("\n\n");
// }

void draw_juicy_line(t_data *texture, t_data *img, t_map *map, t_vector endpoint, t_vector start, t_vector end)
{

	float x = endpoint.x - floor(endpoint.x);

	float y = endpoint.y - floor(endpoint.y);

	// t_data *texture;
	float variant;
	if (x == 0)
	{
		variant = y;
		// if (map->player_position.y < endpoint.y)
		// {
		// 	texture = map->texture_no;
		// }
		// else
		// {
		// 	texture = map->texture_so;
		// }
	}

	if (y == 0)
	{
		variant = x;
		// if (map->player_position.x < endpoint.x)
		// {
		// 	texture = map->texture_ea;
		// }
		// else
		// {
		// 	texture = map->texture_we;
		// }
	}

	int u = (int)(floor(x + y)) % 2;

	int texture_col = (int)floor(variant * 1024);

	float step;
	float dx;
	float dy;
	float i;

	// start.y -100 end.y 1124
	// step 1224
	// dy = 1
	// while 1 < 1224

	step = end.y - start.y;
	// end, start
	dy = step / step;
	i = 0;
	while (i <= step)
	{
		start.y += dy;

		if (start.x < 0 || start.x >= img->line_length || start.y < 0 || start.y >= img->line_length)
		{
			i++;
			continue;
		}

		int texture_row = i * 1023.0 / step;
		// int texture_row = (int)(i * 1023) / 1024;
		int color = get_texture_color(texture, texture_col, texture_row);
		my_mlx_pixel_put(img, start.x, start.y, color);
		i++;
	}
}

void draw_disk(int x, int y, int radius, t_data *img, int color)
{
	int i;
	int dx;
	int dy;

	i = x - radius;
	while (i <= x + radius)
	{
		int j;

		j = y - radius;
		while (j <= y + radius)
		{
			if (i < 0 || i >= img->line_length || j < 0 || j >= img->line_length)
			{
				continue;
			}
			dx = i - x;
			dy = j - y;
			if (dx * dx + dy * dy <= radius * radius)
			{
				my_mlx_pixel_put(img, i, j, color);
			}
			j++;
		}
		i++;
	}
}
