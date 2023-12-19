/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:21:05 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/19 17:45:54 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	load_textures(t_map *map, t_mlx *mlx)
{
	int	size;

	size = 1024;
	map->texture_no = ft_gc_malloc(sizeof(t_data));
	map->texture_no->img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->no, &size,
			&size);
	map->texture_no->addr = mlx_get_data_addr(map->texture_no->img,
			&map->texture_no->bits_per_pixel, &map->texture_no->line_length,
			&map->texture_no->endian);
	map->texture_so = ft_gc_malloc(sizeof(t_data));
	map->texture_so->img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->so, &size,
			&size);
	map->texture_so->addr = mlx_get_data_addr(map->texture_so->img,
			&map->texture_so->bits_per_pixel, &map->texture_so->line_length,
			&map->texture_so->endian);
	map->texture_we = ft_gc_malloc(sizeof(t_data));
	map->texture_we->img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->we, &size,
			&size);
	map->texture_we->addr = mlx_get_data_addr(map->texture_we->img,
			&map->texture_we->bits_per_pixel, &map->texture_we->line_length,
			&map->texture_we->endian);
	map->texture_ea = ft_gc_malloc(sizeof(t_data));
	map->texture_ea->img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->ea, &size,
			&size);
	map->texture_ea->addr = mlx_get_data_addr(map->texture_ea->img,
			&map->texture_ea->bits_per_pixel, &map->texture_ea->line_length,
			&map->texture_ea->endian);
	map->fight[0] = ft_strdup("textures/xpm/fight/frame1.xpm");
	map->fight[1] = ft_strdup("textures/xpm/fight/frame2.xpm");
	map->fight[2] = ft_strdup("textures/xpm/fight/frame3.xpm");
	map->fight[3] = ft_strdup("textures/xpm/fight/frame4.xpm");
	while (map->fight_index < 4)
	{
		map->texture_fight[map->fight_index] = ft_gc_malloc(sizeof(t_data));
		map->texture_fight[map->fight_index]->img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->fight[map->fight_index], &size,
				&size);
		map->texture_fight[map->fight_index]->addr = mlx_get_data_addr(map->texture_fight[map->fight_index]->img,
				&map->texture_fight[map->fight_index]->bits_per_pixel, &map->texture_fight[map->fight_index]->line_length,
				&map->texture_fight[map->fight_index]->endian);
		map->fight_index++;
	}
	map->fight_index = 0;
	map->door = ft_strdup("textures/xpm/door.xpm");
	map->texture_door = ft_gc_malloc(sizeof(t_data));
	map->texture_door->img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->door, &size,
			&size);
	map->texture_door->addr = mlx_get_data_addr(map->texture_door->img,
			&map->texture_door->bits_per_pixel, &map->texture_door->line_length,
			&map->texture_door->endian);
}

void	load_textures_1(t_map *map, t_mlx *mlx)
{
	int	size;

	size = 1024;
	map->texture_no = ft_gc_malloc(sizeof(t_data));
	map->texture_no->img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->no, &size,
			&size);
	map->texture_no->addr = mlx_get_data_addr(map->texture_no->img,
			&map->texture_no->bits_per_pixel, &map->texture_no->line_length,
			&map->texture_no->endian);
	map->texture_so = ft_gc_malloc(sizeof(t_data));
	map->texture_so->img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->so, &size,
			&size);
	map->texture_so->addr = mlx_get_data_addr(map->texture_so->img,
			&map->texture_so->bits_per_pixel, &map->texture_so->line_length,
			&map->texture_so->endian);
}

void	load_textures_2(t_map *map, t_mlx *mlx)
{
	int	size;

	size = 1024;
	map->texture_we = ft_gc_malloc(sizeof(t_data));
	map->texture_we->img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->we, &size,
			&size);
	map->texture_we->addr = mlx_get_data_addr(map->texture_we->img,
			&map->texture_we->bits_per_pixel, &map->texture_we->line_length,
			&map->texture_we->endian);
	map->texture_ea = ft_gc_malloc(sizeof(t_data));
	map->texture_ea->img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->ea, &size,
			&size);
	map->texture_ea->addr = mlx_get_data_addr(map->texture_ea->img,
			&map->texture_ea->bits_per_pixel, &map->texture_ea->line_length,
			&map->texture_ea->endian);
}
