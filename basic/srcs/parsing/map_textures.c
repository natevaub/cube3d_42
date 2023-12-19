/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:00:48 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/16 14:23:30 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	parse_east_texture(char *line, t_map *map)
{
	char	**texture_info;
	int		count_info;

	texture_info = ft_split(line, ' ');
	if (map->count_ea > 1)
		return ;
	count_info = count_split_elements(texture_info);
	if (ft_strcmp(texture_info[0], "EA") == 0)
	{
		map->count_ea++;
		if (count_info != 2)
			return ;
		check_access_textures(texture_info, map);
		return ;
	}
}

void	parse_west_texture(char *line, t_map *map)
{
	char	**texture_info;
	int		count_info;

	texture_info = ft_split(line, ' ');
	if (map->count_we > 1)
		return ;
	count_info = count_split_elements(texture_info);
	if (ft_strcmp(texture_info[0], "WE") == 0)
	{
		map->count_we++;
		if (count_info != 2)
			return ;
		check_access_textures(texture_info, map);
		return ;
	}
}

void	parse_north_texture(char *line, t_map *map)
{
	char	**texture_info;
	int		count_info;

	texture_info = ft_split(line, ' ');
	if (map->count_no > 1)
		return ;
	count_info = count_split_elements(texture_info);
	if (ft_strcmp(texture_info[0], "NO") == 0)
	{
		map->count_no++;
		if (count_info != 2)
			return ;
		check_access_textures(texture_info, map);
		return ;
	}
}

void	parse_south_texture(char *line, t_map *map)
{
	char	**texture_info;
	int		count_info;

	texture_info = ft_split(line, ' ');
	if (map->count_so > 1)
		return ;
	count_info = count_split_elements(texture_info);
	if (ft_strcmp(texture_info[0], "SO") == 0)
	{
		map->count_so++;
		if (count_info != 2)
			return ;
		check_access_textures(texture_info, map);
		return ;
	}
}

void	check_access_textures(char **texture_info, t_map *map)
{
	char	*texture_types[4];
	char	**destinations[4];
	int		i;

	i = 0;
	texture_types[0] = "EA";
	texture_types[1] = "WE";
	texture_types[2] = "NO";
	texture_types[3] = "SO";
	destinations[0] = &(map->ea);
	destinations[1] = &(map->we);
	destinations[2] = &(map->no);
	destinations[3] = &(map->so);
	while (i < 4)
	{
		if (ft_strcmp(texture_info[0], texture_types[i]) == 0
			&& access(texture_info[1], F_OK) == 0)
		{
			*destinations[i] = ft_strdup(texture_info[1]);
			return ;
		}
		i++;
	}
}
