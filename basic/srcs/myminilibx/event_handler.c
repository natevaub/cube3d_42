/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 00:23:48 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/19 11:03:46 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	key_release(int keycode, t_map *map)
{
	if (keycode == LINUX_CTRL || keycode == MAC_CTRL || keycode == LINUX_SHIFT
		|| keycode == MAC_SHIFT || keycode == LINUX_SPACE
		|| keycode == MAC_SPACE)
		map->speed = SPEED;
	return (0);
}

void	event_manager(t_map *map)
{
	mlx_hook(map->m_mlx.mlx_win, ON_KEYPRESS, 1L << 0, key_press, map);
	mlx_hook(map->m_mlx.mlx_win, ON_KEYUP, 1L << 1, key_release, map);
	mlx_hook(map->m_mlx.mlx_win, ON_DESTROY, 1L << 17, win_close_click, map);
}

int	win_close_click(void)
{
	exit(0);
}
