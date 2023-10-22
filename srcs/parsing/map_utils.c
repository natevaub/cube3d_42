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

int ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
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

void	print_int_values(char *str) {
	if (!str) {
		return;
	}
	for (int i = 0; i < ft_strlen(str); i++) {
		ft_printf("%d ", str[i]);
	}
	ft_printf("\n");
}

char	*front_trim(char *line)
{
	int	i = 0;
	int size = 0; // Initialize size
	int j = ft_strlen(line) - 1;
	char *new_line;

	if (line == NULL)
		return (NULL);

	// Count the number of characters to trim from the end
	while (j >= 0 && (line[j] == ' ' || line[j] == '\n'))
	{
		j--;
		size++;
	}

	new_line = malloc(sizeof(char) * (j + 2)); // Allocate space for the trimmed string
	if (new_line == NULL)
		return (NULL);

	// Copy the non-trimmed characters to new_line
	i = 0;
	while (i <= j)
	{
		new_line[i] = line[i];
		i++;
	}

	new_line[i] = '\0';
	return (new_line);
}


void	free_lines(char *line, char *current_line)
{
	free(line);
	free(current_line);
}

int count_length(char *line)
{
	int i = 0;

	// Skip leading spaces
	while (line[i] && line[i] == ' ')
	{
		i++;
	}

	int j = 0;

	// Count characters until a space or the end of the string
	while (line[i] && line[i] != ' ')
	{
		i++;
		j++;
	}

	return j;
}



int	parse_cub_elements(int fd, t_map *map)
{
	char	*current_line;
	char	*line;
	int		i = 0;
	int		start = 0;
	int		badElements = 0;

	/* Iterate through the .cub file until it reaches the map */
	while ((current_line = get_next_line(fd)) != NULL)
	{
		line = front_trim(current_line);
		if (line[0] == '\0')
		{
			free_lines(line, current_line);
			continue;
		}
		if (mapStart(line) == 1)
		{
			close(fd);
			ft_printf("Fd = %d\n", fd);
			free_lines(line, current_line);
			break;
		}
		ft_printf("[ %s ]   [ %d ]\n", line, i);
		if (unwanted_elements(line) == 1)
		{
			badElements = 1;
			free_lines(line, current_line);
			break;
		}
		parseElements(line, map);
		/* Function map_start */
		free_lines(line, current_line);
		i++;
	}

	/* Check if map contains all textures and colors before parsing map */
	if (is_valid_elements(map) || badElements == 1)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	else {
		ft_printf("Lets parse the map\n");
	}

	/* Parse the map */
	// first_pass_map(map, fd);

	return (0);
}

int	mapStart(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
	{
		i++;
	}
	if (line[i] && line[i] == '1')
	{
		return (1);
	}
	return (0);
}
