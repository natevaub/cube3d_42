/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:09:16 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/19 10:59:05 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
