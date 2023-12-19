/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_door_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:28:14 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/18 18:31:07 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	parse_door_texture(char *line, t_map *map)
{
	if ((line[0] == 'D' && line[1] == ' ')
		|| (line[0] == 'O' && line[1] == ' '))
	{
		map->ct_door = ft_atoi(line + 2);
		if (map->ct_door < 0 || map->ct_door > 1)
			map->ct_door = 0;
	}
}
