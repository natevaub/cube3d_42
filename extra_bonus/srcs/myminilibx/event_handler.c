/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 00:23:48 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/19 20:42:24 by rrouille         ###   ########.fr       */
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
	mlx_mouse_hook(map->m_mlx.mlx_win, mouse_press, map);
	mlx_hook(map->m_mlx.mlx_win, 6, 0, mouse_move, map);
	mlx_hook(map->m_mlx.mlx_win, ON_DESTROY, 1L << 17, win_close_click, map);
}

int	mouse_move(int x, int y, t_map *map)
{
	int			dx;
	float		angle;
	static int	ignore_event = 0;

	if (ignore_event || !map->mouse_view)
	{
		ignore_event = 0;
		return (0);
	}
	dx = x - map->mouse_x;
	angle = dx * MOUSE_SENSIBILITY;
	map->direction = normalize(rotate(map->direction, angle));
	map->mouse_x = x;
	map->mouse_y = y;
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		ignore_event = 1;
		mlx_mouse_move(map->m_mlx.mlx_win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		map->mouse_x = SCREEN_WIDTH / 2;
		map->mouse_y = SCREEN_HEIGHT / 2;
	}
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_map *map)
{
	(void)x;
	(void)y;
	if (keycode == MOUSE_LEFT)
		attack(map);
	if (keycode == MOUSE_RIGHT)
		open_door(map);
	return (0);
}

int	win_close_click(void)
{
	exit(0);
}
