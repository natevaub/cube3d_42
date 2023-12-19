/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:11:15 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/19 17:10:10 by rrouille         ###   ########.fr       */
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

void	draw_wall_slice(t_data *texture, t_data *img,
		t_view_params *p)
{
	t_vector		start;
	t_vector		end;
	t_vector		endpoint;
	t_view_params	*params;
	int				i;

	start = p->beg;
	end = p->end;
	endpoint = p->endpoint;
	params = ft_gc_malloc(sizeof(t_view_params));
	set_juicy_params(params, endpoint, start, end);
	i = -1;
	while (++i <= params->step)
	{
		start.y += params->dy;
		if (start.x < 0 || start.x >= img->line_length || start.y < 0
			|| start.y >= img->line_length)
			continue ;
		params->texture_row = i * 1023.0 / params->step;
		params->color = get_texture_color(texture, params->texture_col,
				params->texture_row);
		my_mlx_pixel_put(img, start.x, start.y, params->color);
	}
}
