/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floor_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:00:11 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/16 14:24:08 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	valid_floor_color(char *floorValues, t_map *map)
{
	char	**parsed_rgb;
	int		count_info;
	int		i;

	i = -1;
	if (count_occurences(floorValues, ',') != 2)
		return (0);
	while (floorValues[++i] != '\0')
	{
		if (ft_isdigit(floorValues[i]) == 0 && floorValues[i] != ',')
			return (0);
	}
	parsed_rgb = ft_split(floorValues, ',');
	count_info = count_split_elements(parsed_rgb);
	if (count_info != 3)
		return (0);
	if (helper_valid_floor_color(parsed_rgb, map) == 0)
		return (0);
	return (1);
}

int	valid_ceiling_color(char *ceilingValues, t_map *map)
{
	char	**parsed_rgb;
	int		count_info;
	int		i;

	i = -1;
	if (count_occurences(ceilingValues, ',') != 2)
		return (0);
	while (ceilingValues[++i] != '\0')
	{
		if (ft_isdigit(ceilingValues[i]) == 0 && ceilingValues[i] != ',')
			return (0);
	}
	parsed_rgb = ft_split(ceilingValues, ',');
	count_info = count_split_elements(parsed_rgb);
	if (count_info != 3)
		return (0);
	if (helper_valid_ceiling_color(parsed_rgb, map) == 0)
		return (0);
	return (1);
}

char	*concat_split(char **split, int i)
{
	char	*concat;
	char	*tmp;
	int		j;

	concat = NULL;
	tmp = ft_strdup("");
	i = 1;
	j = 0;
	while (split[i])
	{
		concat = ft_strjoin(tmp, split[i]);
		tmp = concat;
		j += ft_strlen(split[i]);
		i++;
	}
	concat[j] = '\0';
	return (concat);
}

/**
 * Except for the map, 
 * each type of information from an element can be 
 * separated by one or more space(s).
*/
void	parse_floor(char *line, t_map *map)
{
	char	**floor_info;
	char	*info_concat;
	int		count_info;

	count_info = count_occurences(line, ',');
	floor_info = ft_split(line, ' ');
	if (ft_strcmp(floor_info[0], "F") == 0)
	{
		map->count_floor++;
		if (count_info != 2)
		{
			return ;
		}
		info_concat = concat_split(floor_info, 1);
		valid_floor_color(info_concat, map);
		return ;
	}
}

void	parse_ceiling(char *line, t_map *map)
{
	char	**ceiling_info;
	char	*info_concat;
	int		count_info;

	count_info = count_occurences(line, ',');
	ceiling_info = ft_split(line, ' ');
	if (ft_strcmp(ceiling_info[0], "C") == 0)
	{
		map->count_ceiling++;
		if (count_info != 2)
			return ;
		info_concat = concat_split(ceiling_info, 1);
		valid_ceiling_color(info_concat, map);
		return ;
	}
}
