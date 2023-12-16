/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:06:50 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/16 15:55:52 by rrouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/**
 * mlx
*/
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_data	img;
}	t_mlx;

typedef struct s_mapping
{
	int	from_width;
	int	from_height;
	int	to_width;
	int	to_height;
}	t_mapping;

typedef struct s_help_vars
{
	int	i;
	int	j;
	int	k;
}	t_help_vars;

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_map {
	int				count_ea;
	int				count_no;
	int				count_so;
	int				count_we;
	char			*path;
	char			*so;
	char			*no;
	char			*we;
	char			*ea;
	char 			*fight[4];
	int				fight_mode;
	int				fight_index;
	struct s_data	*texture_no;
	struct s_data	*texture_so;
	struct s_data	*texture_we;
	struct s_data	*texture_ea;
	struct s_data	*texture_fight[4];
	int				count_floor;
	int				count_ceiling;
	int				floor_r;
	int				floor_g;
	int				floor_b;
	int				ceiling_r;
	int				ceiling_g;
	int				ceiling_b;
	int				rows;
	int				columns;
	int				map_start_line;
	char			player_direction;
	char			**map;
	char			**copy;
	t_vector		player_position;
	t_vector		direction;
	t_mlx			m_mlx;
	t_mapping		mapping;
	int				mouse_x;
	int				mouse_y;
	int				frames;
	int				start_time;
}	t_map;

typedef struct s_intersections
{
	int			size;
	t_vector*	points;
}	t_intersections;

typedef struct s_test
{
	t_vector		pos;
	t_vector		dir;
	t_intersections	intersections;
	t_vector		pp;
}	t_test;

typedef struct s_compute
{
	t_vector	*tmp;
	float		xy;
	float		yx;
	float		x_diag_increment;
	float		y_diag_increment;
	t_vector	curr_square;
	t_vector	curr_origin;
	t_vector	test;
	t_vector	n_direction;
	int			next_x;
	int			next_y;
	float		len_x;
	float		len_y;
	float		diag_for_len_x;
	float		diag_for_len_y;
	float		new_origin_x;
	float		new_origin_y;
	float		eps;
	char		x;
}	t_compute;

typedef struct s_minimap_params
{
	t_vector		origin;
	t_vector		fov_start;
	t_vector		fov_end;
	t_vector		fov_start_endpoint;
	t_vector		fov_end_endpoint;
	t_vector		endpoint;
	t_intersections	intersections;
}	t_minimap_params;

#endif