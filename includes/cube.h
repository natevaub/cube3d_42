#ifndef CUBE_H
# define CUBE_H

#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "../libs/mlx_linux/mlx.h"
#include "../libs/ftprintf/ft_printf.h"
#include "../libs/libft/libft.h"
#include "../includes/struct.h"


int		map_valid_char( char **map );

void	init_helper_vars( t_help_vars *vars );

int		parseEastTexture(char *line);

#endif