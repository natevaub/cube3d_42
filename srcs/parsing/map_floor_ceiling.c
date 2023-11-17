/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floor_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:00:11 by nvaubien          #+#    #+#             */
/*   Updated: 2023/11/17 16:05:18 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	parse_floor(char *line, t_map *map)
{
	char	**floor_info;
	int		count_info;

	floor_info = ft_split(line, ' ');
	count_info = count_split_elements(floor_info);
	if (map->count_floor > 1)
	{
		// free_split(floor_info);
		return ;
	}
	if (ft_strcmp(floor_info[0], "F") == 0)
	{
		map->count_floor++;
		if (count_info == 2)
		{
			valid_floor_color(floor_info[1], map);
			// free_split(floor_info);
			return ;
		}
	}
	// free_split(floor_info);
}

void	parse_ceiling(char *line, t_map *map)
{
	char	**ceiling_info;
	int		count_info;

	ceiling_info = ft_split(line, ' ');
	count_info = count_split_elements(ceiling_info);
	if (map->count_ceiling > 1)
	{
		// free_split(ceiling_info);
		return ;
	}
	if (ft_strcmp(ceiling_info[0], "C") == 0)
	{
		map->count_ceiling++;
		if (count_info == 2)
		{
			valid_ceiling_color(ceiling_info[1], map);
			// free_split(ceiling_info);
			return ;
		}
	}
	// free_split(ceiling_info);
}

int	valid_floor_color(char *floorValues, t_map *map)
{
	char	**parsed_rgb;
	int		count_info;
	int		i;
	int		j;

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
	// free_split(parsed_rgb);
	return (1);
}

int	valid_ceiling_color(char *ceilingValues, t_map *map)
{
	char	**parsed_rgb;
	int		count_info;
	int		i;
	int		j;

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
	// free_split(parsed_rgb);
	return (1);
}
