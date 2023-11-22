typedef struct s_help_vars
{
	int	i;
	int	j;
	int	k;
}	t_help_vars;

typedef enum s_direction
{
	NORTH = 1,
	SOUTH = 2,
	EAST = 3,
	WEST = 4
} t_direction;

typedef struct s_info
{
	int	pos_x;
	int	pos_y;
	enum s_direction	direction;
}	t_info;

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
	int		in_game;
	char	**map;
	char	**copy;
	void	*mlx;
	void	*mlx_win;
    int     texWidth;
    int     texHeight;
	t_data	*img;
	t_info	*player_info;
}	t_map;
