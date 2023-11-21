#include "../includes/cube.h"

void	debug_print_int_values(char *str) {
	if (!str) {
		return;
	}
	for (size_t i = 0; i < ft_strlen(str); i++) {
		ft_printf("%d ", str[i]);
	}
	ft_printf("\n");
}

void debug_print_map(const t_map *map) {
	printf("East Texture: %s\n", map->ea ? map->ea : "Not defined");
	printf("North Texture: %s\n", map->no ? map->no : "Not defined");
	printf("South Texture: %s\n", map->so ? map->so : "Not defined");
	printf("West Texture: %s\n", map->we ? map->we : "Not defined");

	printf("Floor Color: ");
	if (map->floor_R >= 0 && map->floor_G >= 0 && map->floor_B >= 0) {
		printf("%d,%d,%d\n", map->floor_R, map->floor_G, map->floor_B);
	} else {
		printf("Not defined\n");
	}

	printf("Ceiling Color: ");
	if (map->ceiling_R >= 0 && map->ceiling_G >= 0 && map->ceiling_B >= 0) {
		printf("%d,%d,%d\n", map->ceiling_R, map->ceiling_G, map->ceiling_B);
	} else {
		printf("Not defined\n");
	}

	printf("Texture Counts:\n");
	printf("East Texture Count: %d\n", map->count_ea);
	printf("North Texture Count: %d\n", map->count_no);
	printf("South Texture Count: %d\n", map->count_so);
	printf("West Texture Count: %d\n", map->count_we);

	printf("Ceiling Count: %d\n", map->count_ceiling);
	printf("Floor Count: %d\n", map->count_floor);

	printf("Rows Count: %d\n", map->rows_count);
	printf("Rows Width: %d\n", map->rows_width);
	printf("Map Copy:\n");
	printf("Map Content:\n");
	if (map->copy) {
		for (int i = 0; map->copy[i]; i++) {
			printf("%s\n", map->copy[i]);
		}
	} else {
		printf("Not defined\n");
	}

	printf("Map Content:\n");
	if (map->map) {
		for (int i = 0; map->map[i]; i++) {
			printf("%s\n", map->map[i]);
		}
	} else {
		printf("Not defined\n");
	}
}

void	init_map(t_map *map, char **av)
{
	map->path = ft_strdup(av[1]);
	map->so = NULL;
	map->no = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->count_no = 0;
	map->count_ea = 0;
	map->count_so = 0;
	map->count_we = 0;
	map->count_floor = 0;
	map->count_ceiling = 0;
	map->floor_R = -1;
	map->floor_G = -1;
	map->floor_B = -1;
	map->ceiling_R = -1;
	map->ceiling_G = -1;
	map->ceiling_B = -1;
	map->rows_count = 0;
	map->rows_width = 0;
	map->map_start_line = 0;
	map->map = NULL;
	map->copy = NULL;
}

// void	free_map(t_map *map)
// {
// 	int	i;

// 	free(map->path);
// 	if (map->copy)
// 	{
// 		free_split(map->copy);
// 		free(map->so);
// 		free(map->no);
// 		free(map->we);
// 		free(map->ea);
// 	}
// 	if (map->map)
// 	{
// 		i = 0;
// 		while (map->map[i])
// 		{
// 			free(map->map[i]);
// 			i++;
// 		}
// 		free(map->map);
// 	}
// }



int	create_rgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_floor_and_ceiling(t_map *map, t_data *img)
{
	int	floor_color;
	int	ceiling_color;
	int	y;
	int	x;

	floor_color = create_rgb(0, map->floor_R, map->floor_G, map->floor_B);
	ceiling_color = create_rgb(0, map->ceiling_R, map->ceiling_G, map->ceiling_B);
	y = -1;
	while (++y < MINIMAP_HEIGHT / 2)
	{
		x = -1;
		while (++x < MINIMAP_WIDTH)
			my_mlx_pixel_put(img, x, y, floor_color);
	}
	y = MINIMAP_HEIGHT / 2 - 1;
	while (++y < MINIMAP_HEIGHT)
	{
		x = -1;
		while (++x < MINIMAP_WIDTH)
			my_mlx_pixel_put(img, x, y, ceiling_color);
	}
}

void	draw_player(int x, int y, int size, t_data *img)
{
	int	color;
	int	i;
	int	j;

	color = create_rgb(0, 0, 0, 0);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_map *map, t_data *img)
{
	int	x;
	int	y;
	int	size = 4;
	int	i, j;

	y = 10;
	x = MINIMAP_WIDTH / 2 - (map->rows_width * size) / 2;
	i = 0; j = 0;
	while (i < map->rows_count)
	{
		while (j < map->rows_width)
		{
			if (map->map[i][j] == '1')
				draw_square_walls(x, y, size, img);
			else if (map->map[i][j] == '0')
				draw_square(x, y, size, img);
			else if (map->map[i][j] == 'E' || map->map[i][j] == 'W' || map->map[i][j] == 'N' || map->map[i][j] == 'S')
				draw_player(x, y, size, img);
			x += size;
			j++;
		}
		i++;
		x = MINIMAP_WIDTH / 2 - (map->rows_width * size) / 2;
		j = 0;
		y += size;
	}
}

void	draw_view(t_map *map, t_data *img)
{
	(void)map;
	(void)img;
	// calculer la distance entre le joueur et le mur d'en face
	// calculer la hauteur du mur
	// calculer la position du mur sur l'écran
	// dessiner le mur
	// sprites in map->so, map->no, map->we, map->ea
	// position of the player in map->player_info->pos_x, map->player_info->pos_y
	// direction of the player in map->player_info->direction (NORTH, SOUTH, EAST, WEST)
}

void	calculate_map(t_map *map)
{
	int	i;
	int	j;
	int	nbr_east = 0;
	int	nbr_west = 0;
	int	nbr_north = 0;
	int	nbr_south = 0;
	i = 0;
	while (i < map->rows_count)
	{
		j = 0;
		while (j < map->rows_width)
		{
			if (map->map[i][j] == 'E')
				nbr_east++;
			else if (map->map[i][j] == 'N')
				nbr_north++;
			else if (map->map[i][j] == 'S')
				nbr_south++;
			else if (map->map[i][j] == 'W')
				nbr_west++;
			j++;
		}
		i++;
	}
	map->player_info = ft_gc_malloc(sizeof(t_info));
	if (!map->player_info)
		return ;
	if (nbr_east == 1)
		map->player_info->direction = EAST;
	else if (nbr_north == 1)
		map->player_info->direction = NORTH;
	else if (nbr_south == 1)
		map->player_info->direction = SOUTH;
	else if (nbr_west == 1)
		map->player_info->direction = WEST;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'E' || map->map[i][j] == 'W' || map->map[i][j] == 'N' || map->map[i][j] == 'S')
			{
				map->player_info->pos_x = j;
				map->player_info->pos_y = i;
			}
			j++;
		}
		i++;
	}
}

int	close_window(t_map *map)
{
	// free(img->player_info);
	// free(img);
	(void)map;
	exit(0);
	return (0);
}

int	player_is_facing_wall(t_map *map)
{
	int	x;
	int	y;

	x = map->player_info->pos_x;
	y = map->player_info->pos_y;
	if (map->player_info->direction == NORTH)
	{
		if (map->map[y - 1][x] == '1')
			return (1);
	}
	else if (map->player_info->direction == SOUTH)
	{
		if (map->map[y + 1][x] == '1')
			return (1);
	}
	else if (map->player_info->direction == EAST)
	{
		if (map->map[y][x + 1] == '1')
			return (1);
	}
	else if (map->player_info->direction == WEST)
	{
		if (map->map[y][x - 1] == '1')
			return (1);
	}
	return (0);
}

int	key_press(int keycode, t_map *map)
{
	if (keycode == KEY_W || keycode == KEY_UP)
	{
		printf("Avancer\n");
		if (player_is_facing_wall(map))
			return (0);
		if (map->player_info->direction == NORTH)
			map->player_info->pos_y--;
		else if (map->player_info->direction == SOUTH)
			map->player_info->pos_y++;
		else if (map->player_info->direction == EAST)
			map->player_info->pos_x++;
		else if (map->player_info->direction == WEST)
			map->player_info->pos_x--;
	}
	else if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		printf("Reculer\n");
		if (player_is_facing_wall(map))
			return (0);
		if (map->player_info->direction == NORTH)
			map->player_info->pos_y++;
		else if (map->player_info->direction == SOUTH)
			map->player_info->pos_y--;
		else if (map->player_info->direction == EAST)
			map->player_info->pos_x--;
		else if (map->player_info->direction == WEST)
			map->player_info->pos_x++;
	}
	else if (keycode == KEY_A || keycode == KEY_LEFT)
	{
		printf("LEFT\n");
		if (player_is_facing_wall(map))
			return (0);
		map->player_info->direction = (map->player_info->direction + 3) % 4;
		if (map->player_info->direction == NORTH)
			map->player_info->pos_y--;
		else if (map->player_info->direction == SOUTH)
			map->player_info->pos_y++;
		else if (map->player_info->direction == EAST)
			map->player_info->pos_x++;
		else if (map->player_info->direction == WEST)
			map->player_info->pos_x--;
	}
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		printf("RIGHT\n");
		if (player_is_facing_wall(map))
			return (0);
		map->player_info->direction = (map->player_info->direction + 1) % 4;
		if (map->player_info->direction == NORTH)
			map->player_info->pos_y--;
		else if (map->player_info->direction == SOUTH)
			map->player_info->pos_y++;
		else if (map->player_info->direction == EAST)
			map->player_info->pos_x++;
		else if (map->player_info->direction == WEST)
			map->player_info->pos_x--;
	}
	else if (keycode == KEY_ESC || keycode == KEY_Q)
	{
		close_window(map);
	}
	return (0);
}

int	key_release(int keycode, t_map *map)
{
	// if (keycode == KEY_W || keycode == KEY_UP)
	// {

	// }
	// else if (keycode == KEY_S || keycode == KEY_DOWN)
	// {
		
	// }
	// else if (keycode == KEY_A || keycode == KEY_LEFT)
	// {
		
	// }
	// else if (keycode == KEY_D || keycode == KEY_RIGHT)
	// {
		
	// }
	(void)keycode;
	(void)map;
	return (0);
}

void	process_events(t_map *map)
{
	mlx_hook(map->mlx_win, 2, 1L<<0, key_press, map);
	mlx_hook(map->mlx_win, 3, 1L<<1, key_release, map);
	mlx_hook(map->mlx_win, 17, 1L<<17, close_window, map);
	// update_player(map);
}

void	process_player(t_map *map)
{
	// check_player_position(map);
	// draw_minimap(map, map->img);
	// mlx_put_image_to_window(mlx, mlx_win, map->img->img, 0, 0);
	// mlx_loop(mlx);
	// draw_minimap(map, map->img);
	(void)map;
}

void	display(t_map *map)
{
	// mlx_put_image_to_window(map->mlx, map->mlx_win, map->img->img, 0, 0);
	// mlx_loop(map->mlx);
	(void)map;
}

void	game_loop(void *mlx, void *mlx_win, t_map *map)
{
	mlx_hook(mlx_win, 2, 1L<<0, key_press, map);
	mlx_hook(mlx_win, 3, 1L<<1, key_release, map);
	mlx_hook(mlx_win, 17, 1L<<17, close_window, map);
	mlx_loop(mlx);

	// // mlx_hook(mlx_win, 2, 1L<<0, key_press, map);
	// // mlx_hook(mlx_win, 3, 1L<<1, key_release, map);
	// // mlx_hook(mlx_win, 17, 1L<<17, close_window, map);
	// map->in_game = 1;
	// while (map->in_game)
	// {
	// 	process_events(map);
	// 	process_player(map);
	// 	display(map);
	// 	// mlx_loop(mlx);
	// 	// check_player_position(map);
	// 	// draw_minimap(map, map->img);
	// 	// mlx_put_image_to_window(mlx, mlx_win, map->img->img, 0, 0);
	// 	// mlx_loop(mlx);
	// }
}

int	main(int ac, char **av )
{
	t_map	map;
	int		code_error;

	if (ac != 2)
	{
		ft_printf("😔 Why are you doing this to me ? 😔\n");
		return (1);
	}
	init_map(&map, av);
	// open_cub_file(map.path, &map);
	code_error = parser(&map);
	if (code_error)
	{
		ft_printf("😔 Why are you doing this to me ? 😔\n");
		return (1);
	}
	else if (!code_error)
		ft_printf("🔥 I'm ready to cast rayzzzz 🔥\n");
	// debug_print_map(&map);

	/* Je fais ma sauce */
	t_data	img;
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT, "Hello world!");
	img.img = mlx_new_image(mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	/*
	** After creating an image, we can call `mlx_get_data_addr`, we pass
	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
	** then be set accordingly for the *current* data address.
	*/
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	// draw_square(10, 20, 50, &img);
	draw_floor_and_ceiling(&map, &img);
	calculate_map(&map);
	// draw_view(&map, &img);
	// minimap_square(&map, &img);
	// minimap_square(&map, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	draw_minimap(&map, &img);
	game_loop(mlx, mlx_win, &map);
	// mlx_loop(mlx);


	/* Memory Management */
	// free_map(&map);
	return (0);
}


