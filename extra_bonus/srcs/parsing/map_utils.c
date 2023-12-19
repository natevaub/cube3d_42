/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:01:23 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/19 07:14:50 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	count_split_elements(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	count_occurences(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	*front_trim(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = ft_strlen(line) - 1;
	while (j >= 0 && (line[j] == ' ' || line[j] == '\n'))
		j--;
	new_line = ft_gc_malloc(sizeof(char) * (j + 2));
	if (new_line == NULL)
		return (NULL);
	i = 0;
	while (i <= j)
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

void	contains_spawns_helper(t_map *map, int *flag, int *i, int *j)
{
	map->player_position.y = *i + 0.5;
	map->player_position.x = *j + 0.5;
	(*flag)++;
}

int	check_position_items(t_map *map, t_vector position, int range, char item)
{
	int	i;
	int	j;

	i = position.y - range;
	while (i <= position.y + range)
	{
		j = position.x - range;
		while (j <= position.x + range)
		{
			if (map->map[i][j] == item)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
