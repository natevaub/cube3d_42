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

int map_valid_char(char **map);

void init_helper_vars(t_help_vars *vars);

/**
 * map_textures.c
 *
 * Norme: ✅ , Leak: ✅
 */
void 	parse_east_texture(char *line, t_map *map);
void 	parse_west_texture(char *line, t_map *map);
void 	parse_north_texture(char *line, t_map *map);
void 	parse_south_texture(char *line, t_map *map);
void 	parseElements(char *line, t_map *map);
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

/**
 *
 *
 *
 */
int count_split_elements(char **tab);
int ft_strcmp(char *s1, char *s2);
void free_split(char **split);
int count_occurences(char *str, char c);
void print_int_values(char *str);

int helper_valid_ceiling_color(char **floorValues, t_map *map);
int helper_valid_floor_color(char **floorValues, t_map *map);
void free_lines(char *line, char *current_line);

int open_cub_file(char *path, t_map *map);
int parse_cub_elements(int fd, t_map *map);
int	cub_copy(int fd, t_map *map);

int cub_parsing(t_map *map);
int mapStart(char *line);

char *front_trim(char *line);
int count_length(char *line);
int first_pass_map(t_map *map, int fd);


#endif