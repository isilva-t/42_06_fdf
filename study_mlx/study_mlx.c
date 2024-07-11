#include "mlx_linux/mlx.h"
#include <X11/keysym.h>

#include <stdlib.h>

typedef struct s_list
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	int		sum_x;
	int		sum_y;
}			t_list;

void free_mlx(t_list *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(1);
}

int	handle_input(int keysym, t_list *data)
{
	if (keysym == XK_Escape)
		free_mlx(data);
	return (0);
}

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
	data.sum_x = 1;
	data.sum_y = 1;
	while (data.y + data.sum_y < 400)
	{
		data.x = 0;
		while (data.x + data.sum_x < 400)
		{
			mlx_pixel_put(data.mlx,
					   data.win,
					   data.x + data.sum_x,
					data.y + data.sum_y,
			   	rand() % 0xf8f8f8);
			data.x += 12;
			if (data.x > 385)
				data.sum_x -= 1;
			if (data.sum_x == 0)
				data.sum_x = 10;
		}
		data.y += 3;
	}
	mlx_key_hook(data.win, handle_input, &data);

	mlx_loop(data.mlx);
	return (0);
}
