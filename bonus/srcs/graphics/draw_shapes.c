/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:09:16 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/19 17:42:51 by rrouille         ###   ########.fr       */
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

void	draw_disk(int x, int y, int radius, t_data *img)
{
	int	i;
	int	dx;
	int	dy;
	int	j;
	int	color;

	i = x - radius - 1;
	color = CYAN;
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
