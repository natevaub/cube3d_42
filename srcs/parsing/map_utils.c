/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:01:23 by nvaubien          #+#    #+#             */
/*   Updated: 2023/10/24 16:02:58 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
	int		size;
	int		j;
	char	*new_line;

	i = 0;
	size = 0;
	j = ft_strlen(line) - 1;
	while (j >= 0 && (line[j] == ' ' || line[j] == '\n'))
	{
		j--;
		size++;
	}
	new_line = malloc(sizeof(char) * (j + 2));
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
