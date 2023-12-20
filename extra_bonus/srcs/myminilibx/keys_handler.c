/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:13:03 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/20 15:36:17 by rrouille         ###   ########.fr       */
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

void	handle_wasd(int kc, t_map *map, t_keycode_helper *h)
{
	normalize((t_vector){.x = -map->direction.y, .y = map->direction.x});
	h->perpendicular.x = -map->direction.y;
	h->perpendicular.y = map->direction.x;
	h->dir = normalize(map->direction);
	h->is_moved = 0;
	if (kc == MAC_A || kc == MAC_D || kc == MAC_W || kc == MAC_S || kc == 0)
	{
		h->is_moved = 1;
		if (kc == LINUX_W || kc == MAC_W)
			h->move = mul_scalar(h->dir, map->speed);
		if (kc == LINUX_A || kc == MAC_A)
			h->move = mul_scalar(h->perpendicular, -map->speed);
		if (kc == LINUX_S || kc == MAC_S)
			h->move = mul_scalar(h->dir, -map->speed);
		if (kc == LINUX_D || kc == MAC_D)
			h->move = mul_scalar(h->perpendicular, map->speed);
	}
	if (h->is_moved)
	{
		h->epsilon = 0.01;
		h->nwpos = add(map->player_position,
				mul_scalar(h->move, 1 + h->epsilon));
		if (map->map[(int)h->nwpos.y][(int)h->nwpos.x] != '1' &&
				map->map[(int)h->nwpos.y][(int)h->nwpos.x] != 'D')
		{
			map->player_position = h->nwpos;
			map->last_position_change = get_current_time();
		}
	}
}

void	handle_esc(int keycode)
{
	if (keycode == LINUX_ESCAPE || keycode == MAC_ESCAPE)
		exit(0);
}

int	key_press(int keycode, t_map *map)
{
	t_keycode_helper *h;

	h = malloc(sizeof(t_keycode_helper));
	if (!h)
		exit(0);
	handle_speed(keycode, map);
	handle_wasd(keycode, map, h);
	handle_arrows(keycode, map);
	handle_esc(keycode);
	if (keycode == LINUX_M || keycode == MAC_M)
	{
		map->mouse_view = !map->mouse_view;
		if (map->mouse_view)
			mlx_mouse_hide();
		else
			mlx_mouse_show();
	}
	return (0);
}

int	win_close_key(t_mlx *m_mlx)
{
	mlx_destroy_window(m_mlx->mlx_ptr, m_mlx->mlx_win);
	exit(0);
}
