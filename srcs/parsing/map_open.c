/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_open.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:00:28 by nvaubien          #+#    #+#             */
/*   Updated: 2023/11/21 14:39:00 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

int	open_cub_file(char *path, t_map *map)
{
	int	fd;

	(void) map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Cannot open ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	return (fd);
}

int	parser(t_map *map)
{
	int	fd;

	fd = open_cub_file(map->path, map);
	if (fd == -1)
		return (1);
	if (manage_errors(cub_copy(fd, map)))
	{
		return (1);
	}
	if (manage_errors(cub_copy_to_map(map)))
	{
		return (1);
	}
	if (manage_errors(map_transform_to_usable(map)))
	{
		return (1);
	}
	return (0);
}

int	cub_copy(int fd, t_map *map)
{
	char	*line;
	char	*to_free;
	char	*res;
	int		map_start_at;

	res = NULL;
	to_free = ft_strdup("");
	line = get_next_line(fd);
	while (line != NULL)
	{
		res = ft_strjoin(to_free, line);
		// free_lines(to_free, line);
		to_free = res;
		line = get_next_line(fd);
	}
	search_map(0, &map_start_at, res);
	if (map_start_at == -1)
	{
		// free(res);
		return (1);
	}
	if (found_empty_line(&res[map_start_at]))
	{
		free(res);
		return (2);
	}
	map->copy = ft_split(res, '\n');
	// free(res);
	return (0);
}

int	cub_copy_to_map(t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (map->copy[i])
	{
		if (map_start(map->copy[i]))
			break ;
		if (unwanted_elements(map->copy[i]))
			return (3);
		parse_elements(map->copy[i], map);
		i++;
	}
	if (!is_valid_elements(map))
	{
		return (4);
	}
	map->map_start_line = i;
	while (map->copy[i])
	{
		if (ft_strlen(map->copy[i]) > (size_t) map->rows_width)
			map->rows_width = ft_strlen(map->copy[i]);
		map->rows_count++;
		i++;
	}
	return (0);
}

int	map_transform_to_usable(t_map *map)
{
	int	i;

	i = 0;
	map->map = (char **)ft_gc_malloc(sizeof(char *) * (map->rows_count + 1));
	if (map->map == NULL)
		return (5);
	map->map[map->rows_count] = NULL;
	while (i < map->rows_count)
	{
		map->map[i] = fill_map(map->copy[map->map_start_line], map);
		i++;
		map->map_start_line++;
	}
	if (!is_valid_map(map))
		return (6);
	return (0);
}
