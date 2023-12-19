/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_open.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:00:28 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/19 14:47:59 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	open_cub_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (ft_strncmp(&path[ft_strlen(path) - 4], ".cub", 4))
	{
		ft_printf("Error\nFile %s is not a .cub file\n", path);
		return (-1);
	}
	else if (fd == -1)
	{
		ft_printf("Error\nCannot open %s\n", path);
		return (-1);
	}
	else if (!get_next_line(open(path, O_RDONLY)))
	{
		ft_printf("Error\nFile %s is empty\n", path);
		return (-1);
	}
	return (fd);
}

int	parser(t_map *map)
{
	int	fd;

	fd = open_cub_file(map->path);
	if (fd == -1)
		return (1);
	if (manage_errors(cub_copy(fd, map)))
		return (1);
	if (manage_errors(cub_copy_to_map(map)))
		return (1);
	if (manage_errors(map_transform_to_parsable(map)))
		return (1);
	if (manage_errors(map_transform_to_usable(map)))
		return (1);
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
		to_free = res;
		line = get_next_line(fd);
	}
	search_map(0, &map_start_at, res);
	err = map_check_found_or_empty(&map_start_at, res);
	if (err)
		return (err);
	map->copy = ft_split(res, '\n');
	return (0);
}

int	map_check_found_or_empty(int *map_start_at, char *res)
{
	if (*map_start_at == -1)
		return (1);
	if (found_empty_line(&res[*map_start_at]))
		return (2);
	return (0);
}

int	cub_copy_to_map(t_map *map)
{
	int		i;

	i = 0;
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
		if (ft_strlen(map->copy[i]) > (size_t)map->columns)
			map->columns = ft_strlen(map->copy[i]);
		map->rows++;
		i++;
	}
	return (0);
}
