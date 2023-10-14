#include "../../includes/cube.h"

/**
 * Check if the characters in the map are valid.
 *
 * This function iterates through each character in the given map and checks if
 * they are valid according to a predefined set of valid characters.
 *
 * @param map A two-dimensional array of characters representing the map.
 *
 * @return 0 if all characters in the map are valid, 1 if there is an invalid character.
 */
int	map_valid_char( char **map )
{
	char		*valid_chars;
	t_help_vars	vars;

	init_helper_vars( &vars );
	valid_chars = "10NSWE ";
	while (map[vars.i] != NULL)
	{
		vars.j = 0;
		while (map[vars.i][vars.j])
		{
			vars.k = 0;
			while (valid_chars[vars.k] != '\0')
			{
				if (map[vars.i][vars.j] != valid_chars[vars.k])
				{
					ft_printf("Map doesn't contain only valid chars\n");
					return (1);
				}
				vars.k++;
			}
			vars.j++;
		}
		vars.i++;
	}
	ft_printf("Map contains only valid chars\n");
	return (0);
}

int	map_valid_config( char **map )
{
	return (0);
}

char	**map_transform( char **map )
{
	return (0);
}

void	init_helper_vars( t_help_vars *vars )
{
	vars->i = 0;
	vars->j = 0;
	vars->k = 0;
}