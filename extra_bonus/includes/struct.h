/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:06:50 by nvaubien          #+#    #+#             */
/*   Updated: 2023/12/20 13:30:45 by rrouille         ###   ########.fr       */
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

typedef enum	e_sound_type
{
	NO_SOUND,
	SOUND_PUNCH,
	SOUND_FART,
	SOUND_DOOR,
	SOUND_STEPS,
	SOUND_VOICE,
} t_sound_type;

typedef struct	s_sounds
{
	char			*path;
	pid_t			pid;
	bool			played;
	bool			playing;
	t_sound_type	type;
}	t_sounds;

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
	char			*fight[4];
	char			*door;
	int				fight_mode;
	int				fight_index;
	int				mouse_view;
	struct s_data	*texture_no;
	struct s_data	*texture_so;
	struct s_data	*texture_we;
	struct s_data	*texture_ea;
	struct s_data	*texture_fight[4];
	struct s_data	*texture_door;
	int				fight_mode_counter;
	time_t			attack_start_time;
	time_t			curr_time;
	time_t			last_position_change;
	int				count_floor;
	int				count_ceiling;
	int				floor_r;
	int				floor_g;
	int				floor_b;
	int				ceiling_r;
	int				ceiling_g;
	int				ceiling_b;
	int				ct_door;
	int				rows;
	int				columns;
	double			speed;
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
	t_sounds		sounds;
}	t_map;

typedef struct s_intersections
{
	int			size;
	t_vector	*points;
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

typedef struct s_view_params
{
	t_vector		origin;
	t_vector		fov_start;
	t_vector		fov_end;
	t_vector		fov_start_endpoint;
	t_vector		fov_end_endpoint;
	t_intersections	intersections;
	int				texture_col;
	int				texture_row;
	int				color;
	float			x;
	float			y;
	float			variant;
	float			step;
	float			dy;
	float			perp_dist;
	float			h;
	float			dx;
	t_vector		start;
	t_vector		end;
	t_vector		line;
	t_vector		n_line;
	t_vector		point;
	t_vector		dir;
	t_vector		endpoint;
	t_vector		dist;
	t_vector		beg;

}	t_view_params;

typedef struct s_keycode_helper
{
	t_vector	perpendicular;
	t_vector	dir;
	t_vector	move;
	t_vector	nwpos;
	float		epsilon;
	int			is_moved;
}	t_keycode_helper;

#endif