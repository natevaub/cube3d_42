/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:13:03 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/19 15:34:10 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	handle_arrows(int keycode, t_map *map)
{
	if (keycode == LINUX_EAST_ARROW || keycode == MAC_EAST_ARROW)
		map->direction = normalize(rotate(map->direction, 2));
	if (keycode == LINUX_WEST_ARROW || keycode == MAC_WEST_ARROW)
		map->direction = normalize(rotate(map->direction, -2));
}

// void	handle_wasd(int keycode, t_map *map)
// {
// 	t_vector	perpendicular;
// 	t_vector	dir;
// 	t_vector	move;
// 	t_vector	new_position;
// 	float		epsilon;
// 	int			is_moved;

// 	perpendicular = normalize((t_vector){.x = -map->direction.y, .y = map->direction.x});
// 	dir = normalize(map->direction);
// 	is_moved = 0;
// 	if (keycode == LINUX_W || keycode == MAC_W)
// 	{
// 		move =  mul_scalar(dir, 0.1);
// 		is_moved = 1;
// 	}
// 	if (keycode == LINUX_A || keycode == MAC_A)
// 	{
// 		move = mul_scalar(perpendicular, -0.1);
// 		is_moved = 1;
// 	}
// 	if (keycode == LINUX_S || keycode == MAC_S)
// 	{
// 		move = mul_scalar(dir, -0.1);
// 		is_moved = 1;
// 	}
// 	if (keycode == LINUX_D || keycode == MAC_D)
// 	{
// 		move = mul_scalar(perpendicular, 0.1);
// 		is_moved = 1;
// 	}
// 	if (is_moved)
// 	{
// 		epsilon = 0.01;
// 		new_position = add(map->player_position, mul_scalar(move, 1+epsilon));
// 		if (map->map[(int)new_position.y][(int)new_position.x] != '1')
// 			map->player_position = new_position;
// 	}
// }

void	handle_wasd(int keycode, t_map *map)
{
	t_vector	perpendicular;
	t_vector	dir;
	t_vector	move;
	t_vector	new_position;
	float		epsilon;
	int			is_moved;

	perpendicular = normalize((t_vector){.x = -map->direction.y, .y = map->direction.x});
	dir = normalize(map->direction);
	is_moved = 0;
	if (keycode == LINUX_W || keycode == MAC_W)
	{
		move =  mul_scalar(dir, 0.1);
		is_moved = 1;
	}
	if (keycode == LINUX_A || keycode == MAC_A)
	{
		move = mul_scalar(perpendicular, -0.1);
		is_moved = 1;
	}
	if (keycode == LINUX_S || keycode == MAC_S)
	{
		move = mul_scalar(dir, -0.1);
		is_moved = 1;
	}
	if (keycode == LINUX_D || keycode == MAC_D)
	{
		move = mul_scalar(perpendicular, 0.1);
		is_moved = 1;
	}
	if (is_moved)
	{
		epsilon = 0.01;
		new_position = add(map->player_position, mul_scalar(move, 1+epsilon));
		if (map->map[(int)new_position.y][(int)new_position.x] != '1')
			map->player_position = new_position;
	}
}

void	handle_esc(int keycode)
{
	if (keycode == LINUX_ESCAPE || keycode == MAC_ESCAPE)
		exit(0);
}

int	key_press(int keycode, t_map *map)
{
	handle_speed(keycode, map);
	handle_wasd(keycode, map);
	handle_arrows(keycode, map);
	handle_esc(keycode);
	return (0);
}

int	win_close_key(t_mlx *m_mlx)
{
	mlx_destroy_window(m_mlx->mlx_ptr, m_mlx->mlx_win);
	exit(0);
}
