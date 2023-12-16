/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:31:29 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/16 12:39:05 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	main(int ac, char **av)
{
	t_map		map;
	t_mapping	mapping;
	t_mlx		m_mlx;
	int			code_error;

	(void)ac;
	init_map(&map, av);
	code_error = parser(&map);
	if (code_error)
	{
		// free_map(&map);
		ft_printf("😔 Why are you doing this to me ? 😔\n");
		return (1);
	}
	else if (!code_error)
		ft_printf("🔥 I'm ready to cast rayzzzz 🔥\n");
	debug_print_map(&map);
	init_mapping(&map, &mapping);
	init_mlx(&m_mlx);
	map.m_mlx = m_mlx;
	map.mapping = mapping;
	game_loop(&map);
	// free_map(&map);
	return (0);
}
