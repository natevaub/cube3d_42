typedef struct s_help_vars {
	int	i;
	int	j;
	int	k;
}	t_help_vars;

typedef struct s_map {
	int		count_ea;
	int		count_no;
	int		count_so;
	int		count_we;
	char	*path;
	char	*so;
	char	*no;
	char	*we;
	char	*ea;
	int		count_floor;
	int		count_ceiling;
	int		floor_R;
	int		floor_G;
	int		floor_B;
	int		ceiling_R;
	int		ceiling_G;
	int		ceiling_B;
	int		rows_count;
	int		rows_width;
	int		map_start_line;
	char	**map;
	char	**copy;
}	t_map;

/**
 * mlx
*/
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_mlx {
	void	*mlx;
	void	*mlx_win;
	t_data	*img;
}	t_mlx;


typedef struct s_vector {
	float x;
	float y;
} t_vector;

typedef struct s_mapping {
	int from_width;
	int from_height;
	int to_width;
	int to_height;
} t_mapping;

	

typedef struct s_intersections
{
	int size;
	t_vector* points;
} t_intersections;