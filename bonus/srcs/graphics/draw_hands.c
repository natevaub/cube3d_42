/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hands.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:07:20 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/19 18:07:30 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_hand(t_map *map, t_data *img)
{
	t_vector	loop;
	t_vector	new_size;
	t_vector	offset;
	t_vector	others;

	others.x = 2;
	new_size.x = SCREEN_WIDTH / others.x;
	new_size.y = SCREEN_HEIGHT / others.x;
	offset.x = (SCREEN_WIDTH - new_size.x) / 2;
	offset.y = SCREEN_HEIGHT - new_size.y;
	loop.x = -1;
	while (++loop.x < new_size.x)
	{
		loop.y = -1;
		while (++loop.y < new_size.y)
		{
			others.y = get_texture_color(map->texture_fight[map->fight_index],
					loop.x * others.x, loop.y * others.x);
			if (others.y != -16777216)
				my_mlx_pixel_put(img, loop.x + offset.x, loop.y + offset.y,
					others.y);
		}
	}
}
