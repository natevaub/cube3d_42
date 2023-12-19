/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:31:29 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/18 19:07:24 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int ac, char **av)
{
	int code_error;
	t_map map;

	if (ac != 2)
	{
		ft_printf("😔 Why are you doing this to me ? 😔\n");
		return (1);
	}
	init_map(&map, av);
	code_error = parser(&map);
	if (code_error)
	{
		ft_printf("😔 Why are you doing this to me ? 😔\n");
		return (1);
	}
	init_mapping(&map, &map.mapping);
	init_mlx(&map.m_mlx);
	game_loop(&map);
	return (0);
}
