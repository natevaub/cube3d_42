/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:00:32 by nvaubien          #+#    #+#             */
/*   Updated: 2023/11/01 16:10:46 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

int	is_valid_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map[i])
	{
		if (!contains_only_valid(map->map[i]))
			return (0);
		if ((i == 0 || i == map->rows_count) && !contains_only_1(map->map[i]))
			return (0);
		if (!contains_1_start_end(map->map[i]))
			return (0);
		i++;
	}
	if (contains_spawn(map->map) == 0)
		return (0);
	return (1);
}

int	contains_only_1(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
		{
			ft_putstr_fd(ERR_MSG_1, 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	contains_only_valid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
		{
			ft_putstr_fd(ERR_MSG_2, 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	contains_1_start_end(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (i == 0 || i == ft_strlen(line) - 1)
		{
			if (line[i] != '1')
			{
				ft_putstr_fd(ERR_MSG_1, 2);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	contains_spawn(char **map)
{
	int	flag;
	int	i;
	int	j;

	flag = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
				flag++;
			j++;
		}
		i++;
	}
	if (flag != 1)
	{
		ft_putstr_fd(ERR_MSG_3, 2);
		return (0);
	}
	return (1);
}
