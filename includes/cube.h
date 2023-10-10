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

#define DEBUG 1


int		map_valid_char( char **map );

void	init_helper_vars( t_help_vars *vars );

int		parseEastTexture(char *line, t_map *map);

int		count_split_elements(char **tab);
int		ft_strcmp(char *s1, char *s2);
void	free_split(char **split);
int		count_occurences(char *str, char c);

int		parseFloor(char *line, t_map *map);
int		validFloorColor(char *floorValues, t_map *map);
int		helper_validFloorColor(char **floorValues, t_map *map);


#endif