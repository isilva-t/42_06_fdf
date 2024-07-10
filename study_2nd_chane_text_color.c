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
	int		color;
}			t_mlx_data;

typedef unsigned char	byte;

int	handle_input(int keysym, t_mlx_data *data)
{
	//keycode is appended to key hardware
	//keysym is appended to keyboard layout configuration,
	//so, keysym is more portable and adaptive
	if (keysym == XK_Escape)
	{
		printf("The %d key (ESC) has been pressed\n\n", keysym);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	printf("key \"%d\" pressed\n\n", keysym);
	sleep (2);
	return (1);
}

int	change_color(t_mlx_data *data)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, 150, 150, data->color, "color text test");
	if (data->color == 0xFF0000)
		data->color = 0x00FF00;
	else if (data->color == 0x00FF00)
		data->color = 0x0000FF;
	else
		data->color = 0xFF0000;
	return (0);
}
/*
void	color_screen(t_mlx_data *data, int color)
{
	int	y = 0;
	int	x = 0;

	while (++y < SIDE_LEN)
	{
		while (++x < SIDE_LEN)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
		}
	}
}

int encode_rgb(byte red, byte green, byte blue)
{
	return (red << 16 | green << 8 | blue);
}*/

int	main ()
{
	t_mlx_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	
	data.win_ptr = mlx_new_window(data.mlx_ptr, 400, 400, "my_window");
	data.color = 0xFF0000;
	if (!data.win_ptr)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}
	
	mlx_key_hook(data.win_ptr, handle_input , &data);
	
	mlx_loop_hook(data.mlx_ptr, change_color, &data);

	mlx_loop(data.mlx_ptr);

	//destroy
	//free
}
