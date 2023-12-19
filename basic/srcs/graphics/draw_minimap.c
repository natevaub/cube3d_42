/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:41:26 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/19 13:08:23 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_minimap(t_map *map, t_data *img)
{
	t_vector	start;
	int			size;
	int			i;
	int			j;

	start = (t_vector){.x = SCREEN_WIDTH / 2 - (map->columns * MAP_SCALE) / 2,
		.y = 10};
	size = MAP_SCALE;
	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->columns)
		{
			if (map->map[i][j] == '1')
				draw_square_walls(start.x, start.y, size, img);
			else if (map->map[i][j] == 'D')
				draw_door(start.x, start.y, size, img);
			else if (map->map[i][j] == 'O')
				draw_open_door(start.x, start.y, size, img);
			else
				draw_square(start.x, start.y, size, img);
			start.x += MAP_SCALE;
		}
		start.x = SCREEN_WIDTH / 2 - (map->columns * MAP_SCALE) / 2;
		j = 0;
		start.y += MAP_SCALE;
	}
}

void	draw_player(t_map *map, t_data *img)
{
	t_view_params	params;
	t_vector		mapped;

	// draw_intersections(map, img);
	mapped = map_vec_adjust(map->player_position, map);
	draw_disk(mapped.x, mapped.y, 3, img, GREEN);
	params.fov_start = map_vec(rotate(map->direction, -FOV / 2), map);
	params.fov_end = map_vec(rotate(map->direction, FOV / 2), map);
	params.origin = map_vec_adjust(map->player_position, map);
	params.fov_start_endpoint = add(params.fov_start, params.origin);
	params.intersections = compute_intersections(map->player_position,
			params.fov_start, map);
	params.endpoint = params.intersections.points[params.intersections.size
		- 1];
	params.endpoint = map_vec_adjust(params.endpoint, map);
	draw_line(img, params.origin, params.endpoint, BLUE);
	params.intersections = compute_intersections(map->player_position,
			params.fov_end, map);
	params.endpoint = params.intersections.points[params.intersections.size
		- 1];
	params.endpoint = map_vec_adjust(params.endpoint, map);
	draw_line(img, params.origin, params.endpoint, BLUE);
}

void	draw_floor_ceiling(t_map *map, t_data *img)
{
	int	i;
	int	j;

	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		j = -1;
		while (++j < SCREEN_HEIGHT / 2)
		{
			my_mlx_pixel_put(img, i, j, encode_rgb(0, map->ceiling_r,
					map->ceiling_g, map->ceiling_b));
		}
	}
	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		j = SCREEN_HEIGHT / 2 - 1;
		while (++j < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(img, i, j, encode_rgb(0, map->floor_r,
					map->floor_g, map->floor_b));
		}
	}
}

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
}

int	get_texture_color(t_data *texture, int x, int y)
{
	int	color;

	color = *(int *)(texture->addr + (y * texture->line_length + x
				* (texture->bits_per_pixel / 8)));
	return (color);
}
