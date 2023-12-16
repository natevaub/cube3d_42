/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:13:09 by rrouille          #+#    #+#             */
/*   Updated: 2023/12/16 13:16:09 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	debug_print_int_values(char *str)
{
	size_t	i;

	i = -1;
	if (!str)
		return ;
	while (++i < ft_strlen(str))
		ft_printf("%d ", str[i]);
	ft_printf("\n");
}

void	debug_print_map(const t_map *map)
{
	int	i;

	i = -1;
	printf("East Texture: %s\n", map->ea ? map->ea : "Not defined");
	printf("North Texture: %s\n", map->no ? map->no : "Not defined");
	printf("South Texture: %s\n", map->so ? map->so : "Not defined");
	printf("West Texture: %s\n", map->we ? map->we : "Not defined");
	printf("Floor Color: ");
	if (map->floor_r >= 0 && map->floor_g >= 0 && map->floor_b >= 0)
		printf("%d,%d,%d\n", map->floor_r, map->floor_g, map->floor_b);
	else
		printf("Not defined\n");
	printf("Ceiling Color: ");
	if (map->ceiling_r >= 0 && map->ceiling_g >= 0 && map->ceiling_b >= 0)
		printf("%d,%d,%d\n", map->ceiling_r, map->ceiling_g, map->ceiling_b);
	else
		printf("Not defined\n");
	printf("Texture Counts:\n");
	printf("East Texture Count: %d\n", map->count_ea);
	printf("North Texture Count: %d\n", map->count_no);
	printf("South Texture Count: %d\n", map->count_so);
	printf("West Texture Count: %d\n", map->count_we);
	printf("Ceiling Count: %d\n", map->count_ceiling);
	printf("Floor Count: %d\n", map->count_floor);
	printf("Rows Count: %d\n", map->rows);
	printf("Rows Width: %d\n", map->columns);
	printf("Map Copy:\n");
	printf("Map Content:\n");
	if (map->copy)
	{
		while (map->copy[++i])
			printf("%s\n", map->copy[i]);
	}
	else
		printf("Not defined\n");
	printf("Map Content:\n");
	if (map->map)
	{
		i = -1;
		while (map->map[++i])
			printf("%s\n", map->map[i]);
	}
	else
		printf("Not defined\n");
}
