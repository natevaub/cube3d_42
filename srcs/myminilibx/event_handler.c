/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 00:23:48 by nvaubien          #+#    #+#             */
/*   Updated: 2023/11/25 15:38:19 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	event_manager(t_map *map)
{
	mlx_hook(map->m_mlx.mlx_win, ON_KEYPRESS, 1L<<0, key_press, map);
	mlx_hook(map->m_mlx.mlx_win, ON_DESTROY, 1L << 17, win_close_click, map);
}

int	key_press(int keycode, t_map *map)
{
// printf("Keycode: %d\n", keycode);
	// printf("\nPlayer position: %f, %f\n", map->player_position.x, map->player_position.y);
	handle_wasd(keycode, map);
	handle_arrows(keycode, map);
	handle_esc(keycode, map);
	return (0);
}

int	win_close_click()
{
	exit(0);
}

int	win_close_key(t_mlx *m_mlx)
{
	exit(0);
}

void	handle_arrows(int keycode, t_map *map)
{
	if (keycode == LINUX_EAST_ARROW)
	{
		map->direction = normalize(rotate(map->direction, 2));
	}
	if (keycode == LINUX_WEST_ARROW)
	{
		map->direction = normalize(rotate(map->direction, -2));
	}
}

void	handle_wasd(int keycode, t_map *map)
{

	t_vector perpendicular = normalize((t_vector){.x = -map->direction.y, .y = map->direction.x});
	t_vector dir = normalize(map->direction);

	t_vector  move;
	int is_moved = 0;
	if (keycode == LINUX_W)
	{
		move =  mul_scalar(dir, 0.1);
		is_moved = 1;
	}
	if (keycode == LINUX_A)
	{
		move = mul_scalar(perpendicular, -0.1);
		is_moved = 1;
	}
	if (keycode == LINUX_S)
	{
		move = mul_scalar(dir, -0.1);
		is_moved = 1;
	}
	if (keycode == LINUX_D)
	{
		move = mul_scalar(perpendicular, 0.1);
		is_moved = 1;
	}

	if (is_moved)
	{
		float epsilon = 0.001;
		t_vector new_position = add(map->player_position, mul_scalar(move, 1+epsilon));
		
		if (map->map[(int)new_position.y][(int)new_position.x] != '1')
		{
			map->player_position = new_position;
		}
	}
}

void	handle_esc(int keycode, t_map *map)
{
	if (keycode == LINUX_ESCAPE)
	{
		exit(0);
	}
}