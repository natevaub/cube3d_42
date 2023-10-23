#ifndef CUBE_H
#define CUBE_H

#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>

// #include "../libs/mlx_linux/mlx.h"
#include "../libs/libmlx/mlx.h"
#include "../libs/ftprintf/ft_printf.h"
#include "../libs/libft/libft.h"
#include "../includes/struct.h"

#define DEBUG 1
#define ERR_MSG_1 "Error: Map is not surrounded by 1's\n"
#define ERR_MSG_2 "Error: Map contains invalid characters\n"
#define ERR_MSG_3 "Error: Map does't contains a spawn or contains multiple ones\n"
#define ERR_MSG_4 "Error: Map not found\n"
#define ERR_MSG_5 "Error: Invalid number of textures\n"
#define ERR_MSG_6 "Error: Invalid texture path\n"
#define ERR_MSG_7 "Error: Invalid number of floor & ceiling informations\n"
#define ERR_MSG_8 "Error: Invalidd color\n"


/**
 * map_textures.c
 *
 * Norme: ✅ , Leak: ✅
 */
void 	parse_east_texture(char *line, t_map *map);
void 	parse_west_texture(char *line, t_map *map);
void 	parse_north_texture(char *line, t_map *map);
void 	parse_south_texture(char *line, t_map *map);
void 	parse_elements(char *line, t_map *map);
void 	check_access_textures(char **texture_info, t_map *map,
						   int count_info);

/**
 * map_floor_ceiling.c
 *
 * Norme: ❌ , Leak: ✅
 */
void 	parse_floor(char *line, t_map *map);
void 	parse_ceiling(char *line, t_map *map);
int 	valid_ceiling_color(char *ceilingValues, t_map *map);
int 	valid_floor_color(char *floorValues, t_map *map);

/**
 * map_search.c
 *
 * Norme: ✅ , Leak: ✅
 */
void 	search_map(int i, int *res, char *raw);
int 	search_map_end(int *i, int *res, char *raw);
int 	search_map_1(int *i, int *res, char *raw);
int 	found_empty_line(char *raw);

/**
 * map_errors.c
 *
 * Norme: ❌ , Leak: ✅
 */
int 	unwanted_elements(char *line);
int 	is_valid_elements(t_map *map);
void 	free_lines(char *line, char *current_line);
void	free_split(char **split);

/**
 * map_parsing.c
 *
 * Norme: ❌ , Leak: ✅
 */
int		is_valid_map(t_map *map);;
int		contains_only_valid(char *line);
int		contains_only_1(char *line);
int		contains_1_start_end(char *line);
int		contains_spawn(char **map);

/**
 * map_helpers.c
 *
 * Norme: ❌ , Leak: ✅
 */
int		helper_valid_ceiling_color(char **ceilingValues, t_map *map);
int		helper_valid_floor_color(char **floorValues, t_map *map);
void	parse_elements(char *line, t_map *map);
int		map_start(char *line);
char	*fill_map(char *line, t_map *map);

/**
 * map_utils.c
 *
 * Norme: ❌ , Leak: ✅
 */

int		count_split_elements(char **tab);
int 	ft_strcmp(char *s1, char *s2);
int		count_occurences(char *str, char c);
char	*front_trim(char *line);

/**
 * map_open.c
 *
 * Norme: ❌ , Leak: ✅
 */
int open_cub_file(char *path, t_map *map);
int	cub_copy(int fd, t_map *map);


/**
 *
 *
 *
 */
void debug_print_int_values(char *str);
void debug_print_map(const t_map *map);





// int count_length(char *line);






#endif