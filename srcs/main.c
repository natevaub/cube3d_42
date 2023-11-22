#include "../includes/cube.h"

// int main(int ac, char **av)
// {
// 	t_map map;
// 	t_data data;
// 	int code_error;

// 	init_map(&map, av);
// 	code_error = parser(&map);
// 	ft_printf("Code error = %d\n", code_error);
// 	if (code_error)
// 	{
// 		debug_print_map(&map);
// 		free_map(&map);
// 		ft_printf("😔 Why are you doing this to me ? 😔\n");
// 		return (1);
// 	}
// 	else if (!code_error)
// 		ft_printf("🔥 I'm ready to cast rayzzzz 🔥\n");
// 	debug_print_map(&map);

// 	/* Je fais ma sauce */
// 	t_mlx graphics;
// 	graphics.img = (t_data *)malloc(sizeof(t_data));

// 	graphics.mlx = mlx_init();
// 	graphics.mlx_win = mlx_new_window(graphics.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
// 	graphics.img->img = mlx_new_image(graphics.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
// 	graphics.img->addr = mlx_get_data_addr(graphics.img->img, &graphics.img->bits_per_pixel, &graphics.img->line_length,
// 										   &graphics.img->endian);
// 	// draw_square(10, 20, 50, &img);
// 	t_mapping	mapping;
// 	init_mapping(&map, &mapping);
// 	ft_printf("Mapping : %d, %d\n", mapping.to_width, mapping.to_height);

// 	t_test test;
// 	test_inter(&map, &mapping, &test);
// 	minimap_square(&map, graphics.img, test.intersections, map_vec(test.pos, mapping), map_vec(test.dir, mapping), &mapping);
// 	draw_player(&map, graphics.img, &mapping);


// 	mlx_put_image_to_window(graphics.mlx, graphics.mlx_win, graphics.img->img, 0, 0);
// 	mlx_loop(graphics.mlx);

// 	/* Memory Management */
// 	free_map(&map);
// 	return (0);
// }

int main(int ac, char **av)
{
	t_map		map;
	t_mlx		m_mlx;
	t_mapping	mapping;
	int			code_error;

	init_map(&map, av);
	code_error = parser(&map);
	if (code_error)
	{
		free_map(&map);
		ft_printf("😔 Why are you doing this to me ? 😔\n");
		return (1);
	}
	else if (!code_error)
		ft_printf("🔥 I'm ready to cast rayzzzz 🔥\n");

	debug_print_map(&map);
	init_mapping(&map, &mapping);
	init_mlx(&m_mlx);

	event_manager(&m_mlx);
	free_map(&map);

	return (0);
}