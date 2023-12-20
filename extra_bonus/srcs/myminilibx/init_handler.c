/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:25:32 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/16 14:24:08 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int init_mlx(t_mlx *m_mlx)
{
	m_mlx->mlx_ptr = mlx_init();
	m_mlx->mlx_win = mlx_new_window(m_mlx->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
									"Cub3D");
	m_mlx->img.img = mlx_new_image(m_mlx->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	m_mlx->img.addr = mlx_get_data_addr(m_mlx->img.img,
										&m_mlx->img.bits_per_pixel, &m_mlx->img.line_length,
										&m_mlx->img.endian);

	m_mlx->minimap.img = mlx_new_image(m_mlx->mlx_ptr, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	m_mlx->minimap.addr = mlx_get_data_addr(m_mlx->minimap.img,
											&m_mlx->minimap.bits_per_pixel, &m_mlx->minimap.line_length,
											&m_mlx->minimap.endian);
	return (0);
}
