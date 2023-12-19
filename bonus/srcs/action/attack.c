/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:53:16 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/19 11:18:07 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	attack(t_map *map)
{
	map->attack_start_time = getCurrentTime();
	map->fight_index = 0;
	map->fight_mode = 1;
}
