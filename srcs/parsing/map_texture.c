#include "../../includes/cube.h"

int	parseEastTexture(char *line)
{
	char	path[256];
	char	*prefix;

	line = ft_strtrim(line, " \t");
	prefix = "EA ";
	if (ft_strncmp(line, prefix, ft_strlen(prefix)) == 0)
	{
		printf("Success");
		return (1);
	}

	ft_printf("ARG: %s\n", line);

	return (0);
}