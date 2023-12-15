/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_open.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:00:28 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/16 00:32:55 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

int	open_cub_file(char *path, t_map *map)
{
	int	fd;

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
	if (manage_errors(map_transform_to_parsable(map)))
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
	int		err;

	res = NULL;
	to_free = ft_strdup("");
	line = get_next_line(fd);
	while (line != NULL)
	{
		res = ft_strjoin(to_free, line);
		free_lines(to_free, line);
		to_free = res;
		line = get_next_line(fd);
	}
	search_map(0, &map_start_at, res);
	err = map_check_found_or_empty(&map_start_at, res);
	if (err)
		return (err);
	map->copy = ft_split(res, '\n');
	free(res);
	return (0);
}

int	map_check_found_or_empty(int *map_start_at, char *res)
{
	if (*map_start_at == -1)
	{
		free(res);
		return (1);
	}
	if (found_empty_line(&res[*map_start_at]))
	{
		free(res);
		return (2);
	}
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
		return (4);
	map->map_start_line = i;
	while (map->copy[i])
	{
		if (ft_strlen(map->copy[i]) > map->columns)
			map->columns = ft_strlen(map->copy[i]);
		map->rows++;
		i++;
	}
	return (0);
}
