/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:00:36 by nvaubien          #+#    #+#             */
/*   Updated: 2023/10/24 16:00:37 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	search_map(int i, int *res, char *raw)
{
	while (raw[i] && raw[i] != '\n')
		i++;
	if (search_map_end(&i, res, raw))
		return ;
	i++;
	if (search_map_1(&i, res, raw))
		return ;
	if (raw[i] == ' ')
	{
		while (raw[i] && raw[i] == ' ')
			i++;
		if (search_map_end(&i, res, raw))
			return ;
		if (search_map_1(&i, res, raw))
			return ;
	}
	search_map(i, res, raw);
}

int	search_map_end(int *i, int *res, char *raw)
{
	if (raw[*i] == '\0')
	{
		*res = -1;
		return (1);
	}
	return (0);
}

int	search_map_1(int *i, int *res, char *raw)
{
	if (raw[*i] == '1')
	{
		*res = *i;
		return (1);
	}
	return (0);
}

int	found_empty_line(char *raw)
{
	int	i;

	i = 0;
	while (raw[i])
	{
		if (raw[i] == '\n' && raw[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}
