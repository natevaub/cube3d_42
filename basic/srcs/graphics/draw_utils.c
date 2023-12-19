/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:11:15 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/19 13:32:33 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (data == NULL || data->addr == NULL )
		return ;
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (dst == NULL)
		return ;
	*(unsigned int *)dst = color;
}

int	encode_rgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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

void	draw_wall_slice(t_data *texture, t_data *img,
		t_vector endpoint, t_vector start, t_vector end)
{
	t_view_params	*params;
	int				i;

	params = ft_gc_malloc(sizeof(t_view_params));
	set_juicy_params(params, endpoint, start, end);
	i = 0;
	while (i <= params->step)
	{
		start.y += params->dy;
		if (start.x < 0 || start.x >= img->line_length || start.y < 0
			|| start.y >= img->line_length)
		{
			i++;
			continue ;
		}
		params->texture_row = i * 1023.0 / params->step;
		params->color = get_texture_color(texture, params->texture_col,
				params->texture_row);
		my_mlx_pixel_put(img, start.x, start.y, params->color);
		i++;
	}
}

void	set_juicy_params(t_view_params *params, t_vector endpoint,
	t_vector start, t_vector end)
{
	params->x = endpoint.x - floor(endpoint.x);
	params->y = endpoint.y - floor(endpoint.y);
	if (params->x == 0)
		params->variant = params->y;
	if (params->y == 0)
		params->variant = params->x;
	params->texture_col = (int)floor(params->variant * 1024);
	params->step = end.y - start.y;
	params->dy = params->step / params->step;
}
