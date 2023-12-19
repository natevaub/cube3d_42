/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:13:03 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/19 17:50:27 by nvaubien         ###   ########.fr       */
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
			h->move = mul_scalar(h->dir, 0.1);
		if (kc == LINUX_A || kc == MAC_A)
			h->move = mul_scalar(h->perpendicular, -0.1);
		if (kc == LINUX_S || kc == MAC_S)
			h->move = mul_scalar(h->dir, -0.1);
		if (kc == LINUX_D || kc == MAC_D)
			h->move = mul_scalar(h->perpendicular, 0.1);
	}
	if (h->is_moved)
	{
		h->epsilon = 0.01;
		h->nwpos = add(map->player_position,
				mul_scalar(h->move, 1 + h->epsilon));
		if (map->map[(int)h->nwpos.y][(int)h->nwpos.x] != '1')
			map->player_position = h->nwpos;
	}
}

void	handle_esc(int keycode)
{
	if (keycode == LINUX_ESCAPE || keycode == MAC_ESCAPE)
		exit(0);
}

int	key_press(int keycode, t_map *map)
{
	t_keycode_helper	*h;

	h = ft_gc_malloc(sizeof(t_keycode_helper));
	handle_wasd(keycode, map, h);
	handle_arrows(keycode, map);
	handle_esc(keycode);
	return (0);
}

int	win_close_key(t_mlx *m_mlx)
{
	mlx_destroy_window(m_mlx->mlx_ptr, m_mlx->mlx_win);
	exit(0);
}
