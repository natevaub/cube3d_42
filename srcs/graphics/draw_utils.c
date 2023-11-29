#include "../includes/cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	if (data == NULL || data->addr == NULL) {
		// ft_printf("Error in My pixel put\n");
		return;
	}
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		// ft_printf("Error in My pixel put\n");
		return;
	}
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (dst == NULL)
	{
		// ft_printf("Error in My pixel put\n");
		return;
	}
	*(unsigned int*)dst = color;
}

int	encode_rgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
