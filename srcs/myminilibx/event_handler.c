/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 00:23:48 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/16 12:53:13 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	event_manager(t_map *map)
{
	mlx_hook(map->m_mlx.mlx_win, ON_KEYPRESS, 1L << 0, key_press, map);
	mlx_mouse_hook(map->m_mlx.mlx_win, mouse_press, map);
	mlx_hook(map->m_mlx.mlx_win, 5, 0, mouse_release, map);
	mlx_hook(map->m_mlx.mlx_win, 6, 0, mouse_move, map);
	mlx_hook(map->m_mlx.mlx_win, ON_DESTROY, 1L << 17, win_close_click, map);
}

int	mouse_move(int x, int y, t_map *map)
{
	int		dx;
	float	angle;

	if (map->mouse_click)
	{
		dx = x - map->mouse_x;
		angle = dx * MOUSE_SENSIBILITY;
		map->direction = normalize(rotate(map->direction, angle));
		map->mouse_x = x;
		map->mouse_y = y;
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_map *map)
{
	(void)button;
	(void)x;
	(void)y;
	map->mouse_click = 0;
	mlx_mouse_show(map->m_mlx.mlx_ptr, map->m_mlx.mlx_win);
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_map *map)
{
	printf("Mouse Press x, y: %d, %d\n", x, y);
	if (keycode == MOUSE_LEFT)
		map->mouse_click = 1;
	else if (keycode == MOUSE_SCROLL_UP)
	{
		map->player_position = add(map->player_position,
				mul_scalar(map->direction, 0.1));
	}
	else if (keycode == MOUSE_SCROLL_DOWN)
	{
		map->player_position = add(map->player_position,
				mul_scalar(map->direction, -0.1));
	}
	mlx_mouse_hide(map->m_mlx.mlx_ptr, map->m_mlx.mlx_win);
	return (0);
}

int	win_close_click(void)
{
	exit(0);
}
