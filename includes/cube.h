/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 23:28:47 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/16 20:00:07 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>


# include "../libs/mlx/mlx.h"
# include "../libs/libft/includes/mylib.h"
# include "../includes/struct.h"
# include "../includes/enums.h"

# define DEBUG 1
# define ERR_MSG_1 "Error: Map is not surrounded by 1's\n"
# define ERR_MSG_2 "Error: Map contains invalid characters\n"
# define ERR_MSG_3 "Error: Map doesn't contains a valid spawn\n"
# define ERR_MSG_4 "Error: Map not found\n"
# define ERR_MSG_5 "Error: Invalid number of textures\n"
# define ERR_MSG_6 "Error: Invalid texture path\n"
# define ERR_MSG_7 "Error: Invalid number of floor & ceiling informations\n"
# define ERR_MSG_8 "Error: Invalid color\n"
# define ERR_MSG_9 "Error: Found empty line in map\n"
# define ERR_MSG_10 "Error: Invalid element found\n"
# define ERR_MSG_11 "MALLOC ERROR\n"
# define ERR_MSG_12 "Error: Hole detected in map\n"

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 1024
# define GAME_WIDTH 500
# define GAME_HEIGHT 500
# define MAP_SCALE 10
# define FOV 66
# define DELAY_THRESHOLD 100

# define RED		0x00FF0000
# define GREEN 		0x0000FF00
# define BLUE		0x000000FF
# define YELLOW		0x00FFFF00
# define CYAN		0x0000FFFF
# define MAGENTA	0x00FF00FF
# define ORANGE		0x00FFA500
# define PINK		0xFFC0CB
# define PURPLE		0x800080
# define BROWN		0xA52A2A
# define LIGHT_GRAY		0xD0D3D4
# define DARK_GRAY		0x515A5A
# define WHITE		0xFFFFFF

# define LINUX_W 119
# define LINUX_A 97
# define LINUX_S 115
# define LINUX_D 100
# define LINUX_EAST_ARROW 65363
# define LINUX_WEST_ARROW 65361
# define LINUX_ESCAPE 65307

# define MAC_W 13
# define MAC_A 0
# define MAC_S 1
# define MAC_D 2
# define MAC_EAST_ARROW 124
# define MAC_WEST_ARROW 123
# define MAC_ESCAPE 53
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define MOUSE_MIDDLE 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define MOUSE_SENSIBILITY 0.5

/* _____ PARSING ______ */
/**
 * map_textures.c
 *
 * Norme: ✅ , Leak: ✅
 */
long getCurrentTime();
void			parse_east_texture(char *line, t_map *map);
void			parse_west_texture(char *line, t_map *map);
void			parse_north_texture(char *line, t_map *map);
void			parse_south_texture(char *line, t_map *map);
void			parse_elements(char *line, t_map *map);
void			check_access_textures(char **texture_info, t_map *map);

/**
 * map_floor_ceiling.c
 *
 * Norme: ✅ , Leak: ✅
 */
void			parse_floor(char *line, t_map *map);
void			parse_ceiling(char *line, t_map *map);
int				valid_ceiling_color(char *ceilingValues, t_map *map);
int				valid_floor_color(char *floorValues, t_map *map);
char			*concat_split(char **split, int i);

/**
 * map_search.c
 *
 * Norme: ✅ , Leak: ✅
 */
void			search_map(int i, int *res, char *raw);
int				search_map_end(int *i, int *res, char *raw);
int				search_map_1(int *i, int *res, char *raw);
int				found_empty_line(char *raw);

/**
 * map_errors.c
 *
 * Norme: ✅ , Leak: ✅
 */
int				unwanted_elements(char *line);
int				is_valid_elements(t_map *map);
int				manage_errors(int code_error);

/**
 * map_parsing.c
 *
 * Norme: ✅ , Leak: ✅
 */
int				is_valid_map(t_map *map);;
int				contains_only_valid(char *line);
int				contains_only_1(char *line);
int				contains_1_start_end(char *line);
int				contains_spawn(char **map, t_map *m);

/**
 * map_helpers.c
 *
 * Norme: ❌ , Leak: ✅
 */
int				helper_valid_ceiling_color(char **ceilingValues, t_map *map);
int				helper_valid_floor_color(char **floorValues, t_map *map);
void			parse_elements(char *line, t_map *map);
int				map_start(char *line);
char			*fill_map(char *line, t_map *map);

/**
 * map_utils.c
 *
 * Norme: ✅ , Leak: ✅
 */

int				count_split_elements(char **tab);
int				count_occurences(char *str, char c);
char			*front_trim(char *line);
void			contains_spawns_helper(t_map *map, int *flag, int *i, int *j);

/**
 * map_open.c
 *
 * Norme: ❌ , Leak: ✅
 */
int				open_cub_file(char *path);
int				cub_copy(int fd, t_map *map);
int				parser(t_map *map);
int				cub_copy_to_map(t_map *map);
int				map_check_found_or_empty(int *map_start_at, char *res);

/**
 * map_transform.c
 *
 * Norme:  , Leak: 
*/
int				map_transform_to_parsable(t_map *map);
int				map_transform_to_usable(t_map *map);
int				map_check_hole(t_map *map);

/**
 * map_init_free.c
 * 
 * Norme: ✅ , Leak: ✅
*/
void			init_map(t_map *map, char **av);

/* _____ GRAPHICS ______ */
/**
 * draw_utils.c
 *
 * Norme: ❌ , Leak: ✅
 */
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				encode_rgb(int t, int r, int g, int b);

/**
 * draw_shapes.c
 *
 * Norme: ✅ , Leak: ✅
 */
void			draw_square(int x, int y, int size, t_data *img);
void			draw_square_walls(int x, int y, int size, t_data *img);
void			draw_disk(int x, int y, int radius, t_data *img, int color);
void			draw_line(t_data *img, t_vector start, t_vector end, int color);
void			draw_juicy_line(t_data *texture, t_data *img, t_vector endpoint, t_vector start, t_vector end);

/**
 * draw_minimap.c
*/
void			draw_floor_ceiling(t_map *map, t_data *img);
void			draw_player(t_map *map, t_data *img);
void			draw_minimap(t_map *map, t_data *img);
void			draw_intersections(t_map *map, t_data *img);
void			draw_view(t_map *map, t_data *img);
void			draw_hand(t_map *map, t_data *img);
void			load_textures(t_map *map, t_mlx *m_mlx);
int				get_texture_color(t_data *texture, int x, int y);


/**
 * render.c
 * 
 * 
*/
void			update_frame(t_map *map);
int				game_loop_callback(t_map *map);
void			game_loop(t_map *map);

/**
 *
 *
 *
 */
void			debug_print_int_values(char *str);
void			debug_print_map(const t_map *map);

/* _____ COMPUTE ______ */
/**
 * compute_init.c
 *
 * Norme: ❌ , Leak: ✅
 */
void			init_mapping(t_map *map, t_mapping *mapping);
void			initialize_compute(t_vector or, t_vector dir, t_compute *compute);
void			update_next_x_and_y(t_vector or, t_vector dir, t_compute *c);
void			update_compute_state(t_compute *c);

/**
 * compute.c
 *
 * Norme: ❌ , Leak: ✅
 */
t_intersections	compute_intersections(t_vector or, t_vector dir, t_map *map);
void			store_intersections(t_compute *c, int *n_inter, t_vector **dynamic_res);
int				check_collision(t_map *map, t_compute *c);

/**
 * op_vectors.c
 *
 * Norme: ❌ , Leak: ✅
 */
t_vector 		map_vec(t_vector v, t_map *m);
t_vector		map_vec_adjust(t_vector v, t_map *m);
float 			norm(t_vector vec);
t_vector 		normalize(t_vector vec);
t_vector 		rotate(t_vector v, float angle);

/**
 * op_vectors2.c
 *
 * Norme: ❌ , Leak: ✅
 */
t_vector 		add(t_vector a, t_vector b);
t_vector		sub_vector(t_vector a, t_vector b);
t_vector 		add_scalar(t_vector a, float b);
t_vector 		mul_scalar(t_vector a, float b);
t_vector		transform_pdirection_to_vector(char direction);

/* _____ MYMINILIBX ______ */
/**
 * init_handler.c
 *
 * Norme: ❌ , Leak: ✅
 */
int				init_mlx(t_mlx *m_mlx);

/**
 * event_handler.c
 *
 * Norme: ❌ , Leak: ✅
 */
void			event_manager(t_map *map);
int				mouse_move(int x, int y, t_map *map);
int				mouse_release(int button, int x, int y, t_map *map);
int				mouse_press(int keycode, int x, int y, t_map *map);
int				key_press(int keycode, t_map *map);
int				win_close_click();
int				win_close_key(t_mlx *m_mlx);
void			handle_wasd(int keycode, t_map *map);
void			handle_arrows(int keycode, t_map *map);
void			handle_esc(int keycode, t_map *map);

#endif