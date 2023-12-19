/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:53:16 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/19 18:48:21 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	attack(t_map *map)
{
	map->attack_start_time = get_current_time();
	map->fight_index = 0;
	map->fight_mode = 1;
}
