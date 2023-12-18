/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:41:26 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/18 16:45:40 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_door(int x, int y, int size, t_data *img);
void	draw_open_door(int x, int y, int size, t_data *img);

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
	t_minimap_params	params;
	t_vector			mapped;

	draw_intersections(map, img);
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

int	get_texture_color(t_data *texture, int x, int y)
{
	int	color;

	color = *(int *)(texture->addr + (y * texture->line_length + x
				* (texture->bits_per_pixel / 8)));
	return (color);
}

void	draw_view(t_map *map, t_data *img)
{
	int				i;
	float			perp_dist;
	float			h;
	float			dx;
	t_vector		start;
	t_vector		end;
	t_vector		line;
	t_vector		n_line;
	t_vector		point;
	t_vector		dir;
	t_intersections	intersections;
	t_vector		endpoint;
	t_vector		dist;
	t_vector		beg;

	draw_floor_ceiling(map, img);
	start = add(map->player_position, rotate(map->direction, -FOV / 2.0));
	end = add(map->player_position, rotate(map->direction, FOV / 2.0));
	line = sub_vector(end, start);
	n_line = normalize(line);
	dx = norm(line) / SCREEN_WIDTH;
	i = -1;
	while (++i < SCREEN_HEIGHT)
	{
		point = add(start, mul_scalar(n_line, dx * i));
		dir = normalize(sub_vector(point, map->player_position));
		intersections = compute_intersections(map->player_position, dir, map);
		endpoint = intersections.points[intersections.size - 1];
		dist = sub_vector(endpoint, map->player_position);
		perp_dist = norm(dist) * cos(atan2(dir.y, dir.x)
				- atan2(map->direction.y, map->direction.x));
		h = SCREEN_HEIGHT / perp_dist;
		beg = (t_vector){.x = i, .y = SCREEN_HEIGHT / 2 - h / 2};
		end = (t_vector){.x = i, .y = SCREEN_HEIGHT / 2 + h / 2};
		char cell = map->map[(int)endpoint.y][(int)endpoint.x];
		t_data *texture = NULL;
		if (cell == 'D')
			texture = map->texture_door;
		else if (endpoint.y == (int)endpoint.y)
		{
			if (map->player_position.y > endpoint.y)
				texture = map->texture_no;
			else
				texture = map->texture_so;
		}
		else if (endpoint.x == (int)endpoint.x)
		{
			if (map->player_position.x > endpoint.x)
				texture = map->texture_we;
			else
				texture = map->texture_ea;
		}
		if (texture)
			draw_juicy_line(texture, img, endpoint, beg, end);
	}
}

void draw_hand(t_map *map, t_data *img)
{
	int		size;
	int		color;
	int		resize_factor;
	int		j;
	int		i;
	int		new_width;
	int		new_height;
	int		offset_x;
	int		offset_y;

	resize_factor = 2;
	size = 1024;
	new_width = SCREEN_WIDTH / resize_factor;
	new_height = SCREEN_HEIGHT / resize_factor;
	offset_x = (SCREEN_WIDTH - new_width) / 2;
	offset_y = SCREEN_HEIGHT - new_height;
	i = -1;
	while (++i < new_width)
	{
		j = -1;
		while (++j < new_height)
		{
			color = get_texture_color(map->texture_fight[map->fight_index], i * resize_factor, j * resize_factor);
			if (color != -16777216)
				my_mlx_pixel_put(img, i + offset_x, j + offset_y, color);
		}
	}
}


