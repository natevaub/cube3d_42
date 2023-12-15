/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:00:04 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/15 23:55:28 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

int	unwanted_elements(char *line)
{
	char	**test;

	test = ft_split(line, ' ');
	if (ft_strcmp(test[0], "WE") != 0
		&& ft_strcmp(test[0], "EA") != 0
		&& ft_strcmp(test[0], "SO") != 0
		&& ft_strcmp(test[0], "NO") != 0
		&& ft_strcmp(test[0], "F") != 0
		&& ft_strcmp(test[0], "C") != 0
		&& ft_strcmp(test[0], " ") != 0)
	{
		free_split(test);
		return (1);
	}
	free_split(test);
	return (0);
}

int	is_valid_elements(t_map *map)
{
	if (map->count_no != 1 || map->count_ea != 1 || map->count_so != 1
		|| map->count_we != 1)
	{
		ft_putstr_fd(ERR_MSG_5, 2);
		return (0);
	}
	if (map->so == NULL || map->no == NULL || map->we == NULL
		|| map->ea == NULL)
	{
		ft_putstr_fd(ERR_MSG_6, 2);
		return (0);
	}
	if (map->count_floor != 1 || map->count_ceiling != 1)
	{
		ft_putstr_fd(ERR_MSG_7, 2);
		return (0);
	}
	if (map->floor_r == -1 || map->floor_g == -1 || map->floor_b == -1
		|| map->ceiling_r == -1 || map->ceiling_g == -1 || map->ceiling_b == -1)
	{
		ft_putstr_fd(ERR_MSG_8, 2);
		return (0);
	}
	return (1);
}

void	free_lines(char *line, char *current_line)
{
	free(line);
	free(current_line);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	manage_errors(int code_error)
{
	if (code_error)
	{
		if (code_error == 1)
			ft_putstr_fd(ERR_MSG_4, 2);
		else if (code_error == 2)
			ft_putstr_fd(ERR_MSG_9, 2);
		else if (code_error == 3)
			ft_putstr_fd(ERR_MSG_10, 2);
		else if (code_error == 7)
			ft_putstr_fd(ERR_MSG_12, 2);
		return (1);
	}
	return (0);
}
