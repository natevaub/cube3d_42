/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:13:03 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/16 15:42:15 by rrouille         ###   ########.fr       */
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

void	handle_wasd(int keycode, t_map *map)
{
	t_vector	move;
	float		move_speed;
	t_vector	new_position;

	move = (t_vector){0, 0};
	move_speed = 0.1;
	if (keycode == LINUX_W || keycode == MAC_W)
		move = mul_scalar(normalize(map->direction), move_speed);
	else if (keycode == LINUX_S || keycode == MAC_S)
		move = mul_scalar(normalize(map->direction), -move_speed);
	else if (keycode == LINUX_D || keycode == MAC_D)
		move = mul_scalar(normalize((t_vector){-map->direction.y,
					map->direction.x}), move_speed);
	else if (keycode == LINUX_A || keycode == MAC_A)
		move = mul_scalar(normalize((t_vector){map->direction.y,
					-map->direction.x}), move_speed);
	new_position = add(map->player_position, move);
	if (map->map[(int)new_position.y][(int)new_position.x] != '1')
		map->player_position = new_position;
}

void	handle_esc(int keycode, t_map *map)
{
	(void)map;
	if (keycode == LINUX_ESCAPE || keycode == MAC_ESCAPE)
		exit(0);
}

int	key_press(int keycode, t_map *map)
{
	handle_wasd(keycode, map);
	handle_arrows(keycode, map);
	handle_esc(keycode, map);
	return (0);
}

int	win_close_key(t_mlx *m_mlx)
{
	mlx_destroy_window(m_mlx->mlx_ptr, m_mlx->mlx_win);
	exit(0);
}