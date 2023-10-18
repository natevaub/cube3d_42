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
	char	**map;
}	t_map;