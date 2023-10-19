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