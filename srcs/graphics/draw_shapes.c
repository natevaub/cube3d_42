/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:09:16 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/18 18:37:28 by nvaubien         ###   ########.fr       */
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
