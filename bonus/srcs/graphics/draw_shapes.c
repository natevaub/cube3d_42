/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:09:16 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/18 15:05:11 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
				my_mlx_pixel_put(img, x + i, y + j, WHITE);
			else
				my_mlx_pixel_put(img, x + i, y + j, LIGHT_GRAY);
			j++;
		}
		i++;
	}
}

void	draw_door(int x, int y, int size, t_data *img)
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
				my_mlx_pixel_put(img, x + i, y + j, WHITE);
			else
				my_mlx_pixel_put(img, x + i, y + j, BROWN);
			j++;
		}
		i++;
	}
}

void	draw_open_door(int x, int y, int size, t_data *img)
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
				my_mlx_pixel_put(img, x + i, y + j, WHITE);
			else
				my_mlx_pixel_put(img, x + i, y + j, GREEN);
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

void	draw_line(t_data *img, t_vector start, t_vector end, int color)
{
	float	step;
	float	dx;
	float	dy;
	float	i;

	step = fmaxf(fabs(end.x - start.x), fabs(end.y - start.y));
	dx = (end.x - start.x) / step;
	dy = (end.y - start.y) / step;
	i = 0;
	while (i <= step)
	{
		start.x += dx;
		start.y += dy;
		if (start.x < 0 || start.x >= img->line_length || start.y < 0
			|| start.y >= img->line_length)
		{
			continue ;
		}
		my_mlx_pixel_put(img, start.x, start.y, color);
		i++;
	}
}

void	draw_juicy_line(t_data *texture, t_data *img,
		t_vector endpoint, t_vector start, t_vector end)
{
	int		texture_col;
	int		texture_row;
	int		color;
	float	i;
	float	x;
	float	y;
	float	variant;
	float	step;
	float	dy;

	x = endpoint.x - floor(endpoint.x);
	y = endpoint.y - floor(endpoint.y);
	if (x == 0)
		variant = y;
	if (y == 0)
		variant = x;
	texture_col = (int)floor(variant * 1024);
	step = end.y - start.y;
	dy = step / step;
	i = 0;
	while (i <= step)
	{
		start.y += dy;
		if (start.x < 0 || start.x >= img->line_length || start.y < 0
			|| start.y >= img->line_length)
		{
			i++;
			continue ;
		}
		texture_row = i * 1023.0 / step;
		color = get_texture_color(texture, texture_col, texture_row);
		my_mlx_pixel_put(img, start.x, start.y, color);
		i++;
	}
}

void	draw_disk(int x, int y, int radius, t_data *img, int color)
{
	int	i;
	int	dx;
	int	dy;
	int	j;

	i = x - radius - 1;
	while (++i <= x + radius)
	{
		j = y - radius - 1;
		while (++j <= y + radius)
		{
			if (i < 0 || i >= img->line_length || j < 0
				|| j >= img->line_length)
				continue ;
			dx = i - x;
			dy = j - y;
			if (dx * dx + dy * dy <= radius * radius)
				my_mlx_pixel_put(img, i, j, color);
		}
	}
}
