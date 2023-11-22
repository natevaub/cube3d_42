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

void	get_and_draw_player(t_map *map, t_data *img)
{
	int x = map->player_info->pos_x * MINIMAP_SCALE + MINIMAP_WIDTH / 2 - (map->rows_width * MINIMAP_SCALE) / 2;
    int y = map->player_info->pos_y * MINIMAP_SCALE + 10;

	draw_player(x, y, MINIMAP_SCALE, img);
}

void my_mlx_line_put(t_data *img, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
        my_mlx_pixel_put(img, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}


void draw_line(t_map *map, t_data *img)
{
    int start_x, start_y, end_x, end_y;
    int line_length = 20;

	start_x = 0;
	start_y = 0;
	end_x = 0;
	end_y = 0;
    start_x = map->player_info->pos_x * MINIMAP_SCALE + MINIMAP_WIDTH / 2 - (map->rows_width * MINIMAP_SCALE) / 2;
    start_y = map->player_info->pos_y * MINIMAP_SCALE + 10;
    if (map->player_info->direction == NORTH) {
        end_x = start_x;
        end_y = start_y - line_length;
    } else if (map->player_info->direction == SOUTH) {
        end_x = start_x;
        end_y = start_y + line_length;
    } else if (map->player_info->direction == EAST) {
        end_x = start_x + line_length;
        end_y = start_y;
    } else if (map->player_info->direction == WEST) {
        end_x = start_x - line_length;
        end_y = start_y;
    }
    my_mlx_line_put(img, start_x, start_y, end_x, end_y, 0x00FF00);
}


void	draw_minimap(t_map *map, t_data *img)
{
	int	x;
	int	y;
	int	i, j;

	y = 10;
	x = MINIMAP_WIDTH / 2 - (map->rows_width * MINIMAP_SCALE) / 2;
	i = 0; j = 0;
	while (i < map->rows_count)
	{
		while (j < map->rows_width)
		{
			if (map->map[i][j] == '1')
				draw_square_walls(x, y, MINIMAP_SCALE, img);
			else
				draw_square(x, y, MINIMAP_SCALE, img);
			x += MINIMAP_SCALE;
			j++;
		}
		i++;
		x = MINIMAP_WIDTH / 2 - (map->rows_width * MINIMAP_SCALE) / 2;
		j = 0;
		y += MINIMAP_SCALE;
	}
	get_and_draw_player(map, img);
	draw_line(map, img);
}

void draw_wall_slice(t_data *img, int x, int drawStart, int drawEnd, int side)
{
    // Choose wall color based on side
    int color;
    if (side == 1) color = 0x00FF00;
    else           color = 0xFF0000;

    for (int y = drawStart; y < drawEnd; y++)
        my_mlx_pixel_put(img, x, y, color);
}

void	draw_view(t_map *map, t_data *img)
{
	// Player direction vectors
    double dirX = 0, dirY = 0, planeX = 0, planeY = 0;
    const double FOV = 66 * M_PI / 180; // Field of view

    // Set direction and plane based on player's direction
    switch (map->player_info->direction) {
        case NORTH:
            dirX = 0; dirY = -1;
            planeX = tan(FOV / 2); planeY = 0;
            break;
        case SOUTH:
            dirX = 0; dirY = 1;
            planeX = -tan(FOV / 2); planeY = 0;
            break;
        case EAST:
            dirX = 1; dirY = 0;
            planeX = 0; planeY = tan(FOV / 2);
            break;
        case WEST:
            dirX = -1; dirY = 0;
            planeX = 0; planeY = -tan(FOV / 2);
            break;
    }

    for (int x = 0; x < MINIMAP_WIDTH; x++)
    {
        double cameraX = 2 * x / (double)MINIMAP_WIDTH - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;
        int mapX = (int)(map->player_info->pos_x);
        int mapY = (int)(map->player_info->pos_y);
        double sideDistX;
        double sideDistY;
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double perpWallDist;
        int stepX;
        int stepY;

        int hit = 0;
        int side;
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (map->player_info->pos_x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - map->player_info->pos_x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (map->player_info->pos_y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - map->player_info->pos_y) * deltaDistY;
        }

        // Perform DDA
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (map->map[mapY][mapX] == '1')
				hit = 1;
        }

        // Calculate distance projected on camera direction
        if (side == 0)
			perpWallDist = (mapX - map->player_info->pos_x + (1 - stepX) / 2) / rayDirX;
        else
			perpWallDist = (mapY - map->player_info->pos_y + (1 - stepY) / 2) / rayDirY;

        // Calculate height of line to draw on screen
        int lineHeight = (int)(MINIMAP_HEIGHT / perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + MINIMAP_HEIGHT / 2;
        if (drawStart < 0)
			drawStart = 0;
        int drawEnd = lineHeight / 2 + MINIMAP_HEIGHT / 2;
        if (drawEnd >= MINIMAP_HEIGHT)
			drawEnd = MINIMAP_HEIGHT - 1;
		draw_wall_slice(img, x, drawStart, drawEnd, side);
	}
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
	mlx_destroy_window(map->mlx, map->mlx_win);
	exit(0);
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
	float new_x;
	float new_y;
	float move_step = 1.0;

	new_x = map->player_info->pos_x;
	new_y = map->player_info->pos_y;

	if (keycode == KEY_W || keycode == KEY_UP || keycode == KEY_S || keycode == KEY_DOWN)
	{
		if (map->player_info->direction == NORTH)
			new_y += (keycode == KEY_UP) ? -move_step : move_step;
		else if (map->player_info->direction == SOUTH)
			new_y += (keycode == KEY_UP) ? move_step : -move_step;
		else if (map->player_info->direction == EAST)
			new_x += (keycode == KEY_UP) ? move_step : -move_step;
		else if (map->player_info->direction == WEST)
			new_x += (keycode == KEY_UP) ? -move_step : move_step;

		if (map->map[(int)new_y][(int)new_x] != '1') 
		{
			map->player_info->pos_x = new_x;
			map->player_info->pos_y = new_y;
		}
	}
	else if (keycode == KEY_A || keycode == KEY_LEFT || keycode == KEY_D || keycode == KEY_RIGHT)
	{
		if (keycode == KEY_LEFT || keycode == KEY_A) {
			if (map->player_info->direction == NORTH) 
				map->player_info->direction = WEST;
			else if (map->player_info->direction == WEST) 
				map->player_info->direction = SOUTH;
			else if (map->player_info->direction == SOUTH) 
				map->player_info->direction = EAST;
			else if (map->player_info->direction == EAST) 
				map->player_info->direction = NORTH;
		} else {
			if (map->player_info->direction == NORTH) 
				map->player_info->direction = EAST;
			else if (map->player_info->direction == EAST) 
				map->player_info->direction = SOUTH;
			else if (map->player_info->direction == SOUTH) 
				map->player_info->direction = WEST;
			else if (map->player_info->direction == WEST) 
				map->player_info->direction = NORTH;
		}
	}
	else if (keycode == KEY_ESC || keycode == KEY_Q)
		map->in_game = 0;
	return (0);
}

void	process_events(t_map *map)
{
	mlx_hook(map->mlx_win, 2, 1L<<0, key_press, map);
	mlx_hook(map->mlx_win, 17, 1L<<17, close_window, map);
}

void update_frame(t_map *map, t_data img)
{
    mlx_put_image_to_window(map->mlx, map->mlx_win, img.img, 0, 0);
	mlx_destroy_image(map->mlx, img.img);
}

int game_loop_callback(void *param) {
    t_map *map = (t_map *)param;
	t_data	img;

	img.img = mlx_new_image(map->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    draw_floor_and_ceiling(map, &img);
    if (map->in_game)
	{
		draw_minimap(map, &img);
		draw_view(map, &img);
        update_frame(map, img);
	}
	else
		close_window(map);
    return 0;
}

void	game_loop(t_map *map)
{
	process_events(map);
	mlx_loop_hook(map->mlx, game_loop_callback, map);
	mlx_loop(map->mlx);
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

	map.mlx = mlx_init();
	map.mlx_win = mlx_new_window(map.mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT, "Hello world!");
	img.img = mlx_new_image(map.mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	/*
	** After creating an image, we can call `mlx_get_data_addr`, we pass
	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
	** then be set accordingly for the *current* data address.
	*/
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	// draw_square(10, 20, 50, &img);
	// draw_floor_and_ceiling(&map, &img);
	calculate_map(&map);
	// draw_view(&map, &img);
	// minimap_square(&map, &img);
	// minimap_square(&map, &img);
	// draw_minimap(&map, &img);
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	game_loop(&map);
	// mlx_loop(mlx);


	/* Memory Management */
	// free_map(&map);
	return (0);
}


