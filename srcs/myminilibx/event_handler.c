/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 00:23:48 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/11 12:49:49 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	event_manager(t_map *map)
{
	int	mouse_x;
	int	mouse_y;

	mlx_hook(map->m_mlx.mlx_win, ON_KEYPRESS, 1L<<0, key_press, map);
	mlx_mouse_hook(map->m_mlx.mlx_win, mouse_press, map);
	mlx_hook(map->m_mlx.mlx_win, 5, 0, mouse_release, map);
	mlx_hook(map->m_mlx.mlx_win, 6, 0, mouse_move, map);
	mlx_hook(map->m_mlx.mlx_win, ON_DESTROY, 1L << 17, win_close_click, map);
}

int mouse_move(int x, int y, t_map *map) {
	int		dx;
	float	angle;

	if (map->mouse_click) {
		dx = x - map->mouse_x;
		angle = dx * MOUSE_SENSIBILITY;
		map->direction = normalize(rotate(map->direction, angle));
		map->mouse_x = x;
		map->mouse_y = y;
	}
	return (0);
}

int mouse_release(int button, int x, int y, t_map *map) {
	map->mouse_click = 0;
	mlx_mouse_show();
	return (0);
}

int mouse_press(int keycode, int x, int y, t_map *map) {
	if (keycode == MOUSE_LEFT)
	{
		map->mouse_click = 1;
	}
	else if (keycode == MOUSE_SCROLL_UP)
	{
		map->player_position = add(map->player_position, mul_scalar(map->direction, 0.1));
	}
	else if (keycode == MOUSE_SCROLL_DOWN)
	{
		map->player_position = add(map->player_position, mul_scalar(map->direction, -0.1));
	}
	mlx_mouse_hide();
	return (0);
}


int	key_press(int keycode, t_map *map)
{
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
	if (keycode == LINUX_EAST_ARROW || keycode == MAC_EAST_ARROW)
	{
		map->direction = normalize(rotate(map->direction, 2));
	}
	if (keycode == LINUX_WEST_ARROW || keycode == MAC_WEST_ARROW)
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
	printf("keycode: %d\n", keycode);
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
		float epsilon = 0.01;
		t_vector new_position = add(map->player_position, mul_scalar(move, 1+epsilon));
		
		if (map->map[(int)new_position.y][(int)new_position.x] != '1')
		{
			map->player_position = new_position;
		}
	}
}

void	handle_esc(int keycode, t_map *map)
{
	if (keycode == LINUX_ESCAPE || keycode == MAC_ESCAPE)
	{
		exit(0);
	}
}