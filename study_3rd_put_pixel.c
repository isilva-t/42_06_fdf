/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   study_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:03:14 by isilva-t          #+#    #+#             */
/*   Updated: 2024/07/10 11:01:30 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_linux/mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define WIDTH			400
#define HEIGHT			400
#define SIDE_LEN		400

typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}			t_mlx_data;

typedef unsigned char	byte;

int encode_rgb(byte red, byte green, byte blue)
{
	return (red << 16 | green << 8 | blue);
}

void	color_screen(t_mlx_data *data, int color)
{
	int	y = 0;
	int	x = 0;

	while (++y < SIDE_LEN)
	{
		x = 0;
		while (++x < SIDE_LEN)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
		}
	}
}

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_r)
		color_screen(data, encode_rgb(255, 0, 0));
	else if (keysym == XK_g)
		color_screen(data, encode_rgb(0, 255, 0));
	else if (keysym == XK_b)
		color_screen(data, encode_rgb(0, 0, 255));
	else if (keysym == XK_Escape)
	{
		printf("The %d key (ESC) has been pressed\n\n", keysym);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	return (0);
}

int	main ()
{
	t_mlx_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	
	data.win_ptr = mlx_new_window(data.mlx_ptr, 400, 400, "my_window");
	if (!data.win_ptr)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}
	
	mlx_key_hook(data.win_ptr, handle_input , &data);
	
	mlx_loop(data.mlx_ptr);

	//destroy
	//free
}
