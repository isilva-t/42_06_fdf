#include "mlx_linux/mlx.h"

#include <stdlib.h>

typedef struct s_list
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
}			t_list;

int	main ()
{
	t_list	data;

	data.mlx = mlx_init();

	data.win = mlx_new_window(data.mlx, 400, 400, "mywindow");
	if (!data.win)
	{
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (1);
	}

	data.x = 0;
		data.y = 0;
	while (++data.x < 400 && ++data.y <400)
	{
		mlx_pixel_put(data.mlx,
				   data.win,
				   data.x,
				data.y,
			   0xFF0000);
	}
	data.x = 0;
	data.y = 400;
	while (++data.x < 400 && --data.y > 0)
	{
		mlx_pixel_put(data.mlx,
				   data.win,
				   data.x,
				data.y,
			   0xF00000);
	}

	mlx_loop(data.mlx);
}
