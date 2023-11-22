/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 00:23:48 by nvaubien          #+#    #+#             */
/*   Updated: 2023/11/22 02:51:40 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	event_manager(t_mlx *m_mlx)
{
	mlx_hook(m_mlx->mlx_win, ON_KEYPRESS, 1L<<0, key_hook, m_mlx);
	mlx_hook(m_mlx->mlx_win, ON_DESTROY, 1L << 17, win_close_click, m_mlx);
	mlx_loop(m_mlx->mlx_ptr);
}

int	key_hook(int keycode, t_mlx *m_mlx)
{
	ft_printf("Keycode: %d\n", keycode);
	if (keycode == LINUX_ESCAPE)
		win_close_key(m_mlx);
	return (0);
}

int	win_close_click()
{
	exit(0);
}

int	win_close_key(t_mlx *m_mlx)
{
	// mlx_destroy_window(m_mlx->mlx_ptr, m_mlx->mlx_win);
	// mlx_destroy_image(m_mlx->mlx_ptr, m_mlx->img.img);
	exit(0);
}