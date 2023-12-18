/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speed_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:23:16 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/18 18:24:01 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	handle_speed(int keycode, t_map *map)
{
	if (keycode == LINUX_SHIFT || keycode == MAC_SHIFT || keycode == LINUX_CTRL
		|| keycode == MAC_CTRL || keycode == LINUX_SPACE
		|| keycode == MAC_SPACE)
		map->speed *= 2;
	else if (((keycode == LINUX_CTRL || keycode == MAC_CTRL)
			&& (keycode == LINUX_SHIFT || keycode == MAC_SHIFT))
		|| ((keycode == LINUX_SPACE || keycode == MAC_SPACE)
			&& (keycode == LINUX_SHIFT || keycode == MAC_SHIFT))
		|| ((keycode == LINUX_CTRL || keycode == MAC_CTRL)
			&& (keycode == LINUX_SPACE || keycode == MAC_SPACE)))
		map->speed *= 4;
}
