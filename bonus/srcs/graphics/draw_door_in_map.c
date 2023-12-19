/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door_in_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:32:54 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/19 18:33:02 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
