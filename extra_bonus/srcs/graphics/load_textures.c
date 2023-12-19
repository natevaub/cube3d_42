/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:21:05 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/19 18:43:53 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	load_single_texture(t_mlx *mlx, char *file_path, t_data **texture)
{
	int	size;

	size = 1024;
	*texture = ft_gc_malloc(sizeof(t_data));
	(*texture)->img = mlx_xpm_file_to_image(mlx->mlx_ptr, file_path, &size,
			&size);
	(*texture)->addr = mlx_get_data_addr((*texture)->img,
			&(*texture)->bits_per_pixel, &(*texture)->line_length,
			&(*texture)->endian);
}

void	load_main_textures(t_map *map, t_mlx *mlx)
{
	load_single_texture(mlx, map->no, &map->texture_no);
	load_single_texture(mlx, map->so, &map->texture_so);
	load_single_texture(mlx, map->we, &map->texture_we);
	load_single_texture(mlx, map->ea, &map->texture_ea);
}

void	load_fight_textures(t_map *map, t_mlx *mlx)
{
	map->fight[0] = ft_strdup("textures/xpm/fight/frame1.xpm");
	map->fight[1] = ft_strdup("textures/xpm/fight/frame2.xpm");
	map->fight[2] = ft_strdup("textures/xpm/fight/frame3.xpm");
	map->fight[3] = ft_strdup("textures/xpm/fight/frame4.xpm");
	while (map->fight_index < 4)
	{
		load_single_texture(mlx, map->fight[map->fight_index],
			&map->texture_fight[map->fight_index]);
		map->fight_index++;
	}
	map->fight_index = 0;
}

void	load_door_texture(t_map *map, t_mlx *mlx)
{
	map->door = ft_strdup("textures/xpm/door.xpm");
	load_single_texture(mlx, map->door, &map->texture_door);
}

void	load_textures(t_map *map, t_mlx *mlx)
{
	load_main_textures(map, mlx);
	load_fight_textures(map, mlx);
	load_door_texture(map, mlx);
}
