/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 00:23:48 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/02 17:56:51 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	event_manager(t_map *map)
{
	int mouse_x;
	int mouse_y;

	mlx_hook(map->m_mlx.mlx_win, ON_KEYPRESS, 1L<<0, key_press, map);
	// mlx_mouse_get_pos(map->m_mlx.mlx_win, &map->mouse_x, &map->mouse_y);
	// printf("Mouse position: %d, %d\n", map->mouse_x, map->mouse_y);
	mlx_mouse_hook(map->m_mlx.mlx_win, mouse_press, map);
	mlx_hook(map->m_mlx.mlx_win, ON_DESTROY, 1L << 17, win_close_click, map);
}
void	handle_mouse(int keycode, t_map *map)
{
	int mouse_x;
	int mouse_y;

	// mlx_mouse_get_pos(map->m_mlx.mlx_win, &mouse_x, &mouse_y);
	// printf("Mouse position: %d, %d\n", mouse_x, mouse_y);
	if (keycode == MOUSE_LEFT)
	{
		printf("Mouse left\n");
		// printf("Mouse position: %d, %d\n", map->mouse_x, map->mouse_y);
	}
	if (keycode == MOUSE_RIGHT)
	{
		printf("Mouse right\n");
	}
	if (keycode == MOUSE_MIDDLE)
	{
		printf("Mouse middle\n");
	}
	if (keycode == MOUSE_SCROLL_UP)
	{
		printf("Mouse scroll up\n");
	}
	if (keycode == MOUSE_SCROLL_DOWN)
	{
		printf("Mouse scroll down\n");
	}
}

int	mouse_press(int keycode, t_map *map)
{
	// printf("Mouse keycode: %d\n", keycode);
	// printf("\nPlayer position: %f, %f\n", map->player_position.x, map->player_position.y);
	handle_mouse(keycode, map);
	return (0);
}

int	key_press(int keycode, t_map *map)
{
	// printf("Keycode: %d\n", keycode);
	// printf("\nPlayer position: %f, %f\n", map->player_position.x, map->player_position.y);
	handle_wasd(keycode, map);
	handle_arrows(keycode, map);
	handle_esc(keycode, map);
	// if (keycode == LINUX_MOUSE_LEFT || keycode == MAC_MOUSE_LEFT)
	// {
	// 	int mouse_x;
	// 	int mouse_y;

	// 	mlx_mouse_get_pos(map->m_mlx.mlx_win, &mouse_x, &mouse_y);
	// 	printf("Mouse position: %d, %d\n", mouse_x, mouse_y);
	// }
	// handle_mouse(keycode, map);
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
	// printf("keycode: %d\n", keycode);
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
	if (keycode == LINUX_ESCAPE || keycode == MAC_ESCAPE)
	{
		exit(0);
	}
}