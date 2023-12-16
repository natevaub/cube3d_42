/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:25:32 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/16 11:59:31 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	init_mlx(t_mlx *m_mlx)
{
	m_mlx->mlx_ptr = mlx_init();
	m_mlx->mlx_win = mlx_new_window(m_mlx->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Cub3D");
	m_mlx->img.img = mlx_new_image(m_mlx->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	m_mlx->img.addr = mlx_get_data_addr(m_mlx->img.img,
			&m_mlx->img.bits_per_pixel, &m_mlx->img.line_length,
			&m_mlx->img.endian);
	return (0);
}
