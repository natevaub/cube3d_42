/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 00:23:48 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/16 19:36:35 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
	int			dx;
	float		angle;
	static int	ignore_event = 0;

	if (ignore_event)
	{
		ignore_event = 0;
		return (0);
	}
	mlx_mouse_hide();
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
	// if (map->fight_mode == 1)
	// {
	// 	map->fight_index++;
	// 	if (map->fight_index == 4)
	// 	{
	// 		map->fight_index = 0;
	// 		map->fight_mode = 0;
	// 	}
	// }
	return (0);
}

int	mouse_release(int button, int x, int y, t_map *map)
{
	(void)button;
	(void)x;
	(void)y;
	(void)map;
	// map->mouse_click = 0;
	return (0);
}

void	attack(t_map *map)
{

	map->attackStartTime = getCurrentTime();
	// while (map->fight_index < 3)
	// {
	// 	mlx_clear_window(map->m_mlx.mlx_ptr, map->m_mlx.mlx_win);
	// 	map->fight_index++;
	// 	usleep(100000);
	// 	draw_view(map, &map->m_mlx.img);
	// 	draw_minimap(map, &map->m_mlx.img);
	// 	draw_player(map, &map->m_mlx.img);
	// 	draw_hand(map, &map->m_mlx.img);
	// }
	map->fight_index = 0;
	map->fight_mode = 1;
	// 	map->fight_mode_counter++;
	// 	if (map->fight_mode_counter >= DELAY_THRESHOLD)
	// 	{
	// 		map->fight_index++;
	// 		if (map->fight_index == 4)
	// 		{
	// 			map->fight_index = 0;
	// 			map->fight_mode = 0;
	// 		}
	// 		map->fight_mode_counter = 0;
	// 	}
	// }
}

int	mouse_press(int keycode, int x, int y, t_map *map)
{
	if (keycode == MOUSE_LEFT)
		attack(map);
	(void)x;
	(void)y;
	if (keycode == MOUSE_SCROLL_UP)
	{
		map->player_position = add(map->player_position,
				mul_scalar(map->direction, 0.1));
	}
	else if (keycode == MOUSE_SCROLL_DOWN)
	{
		map->player_position = add(map->player_position,
				mul_scalar(map->direction, -0.1));
	}
	return (0);
}

int	win_close_click(void)
{
	exit(0);
}
