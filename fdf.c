/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:20:58 by isilva-t          #+#    #+#             */
/*   Updated: 2024/07/17 17:21:22 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"




t_iterator	set_i(int n)
{
	t_iterator	i;

	i.x = n;
	i.y = n;
	return (i);
}

int	free_mlx(t_mlx *d)
{
	mlx_destroy_image(d->mlx, d->img.img_p);
	mlx_destroy_window(d->mlx, d->win);
	mlx_destroy_display(d->mlx);
	free(d->mlx);
	return (1);
}

void	my_pixel_put(t_img *img, t_iterator i, int color)
{
	int	offset;

	offset = (img->line_len * i.y) + (i.x * (img->bits_per_px / 8));

	*((unsigned int *)(offset + img->img_px_p)) = color;
}

void	color_screen(t_mlx *d, int color)
{
	t_iterator	i;

	i.y = Y_MIN;
	while (++i.y < Y_MAX)
	{
		i.x = X_MIN;
		while (++i.x < X_MAX)
		{
			my_pixel_put(&d->img, i, color);
		}
	}
}

int	handle_input(int key, t_mlx *d)
{
	if (key == XK_r)
	{
		color_screen(d, 0xff0000);
		ft_printf("key %d pressed\n", key);
	}
	else if (key == XK_g)
	{
		color_screen(d, 0x00ff00);
		ft_printf("key %d pressed\n", key);
	}
	else if (key == XK_b)
	{
		color_screen(d, 0x0000ff);
		ft_printf("key %d pressed\n", key);
	}
	else if (key == XK_Escape)
	{
		printf("The %d key (ESC) has been pressed\n\n", key);
		free_stuff(d->map);
		exit(free_mlx(d));
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img.img_p, 0, 0);
	return (0);
}

int	mouse_hook(int mkey, t_mlx *d)
{
	if (!d)
		return (1);
	if (mkey == 1)
	{
		ft_printf("mouse %d (left key) pressed\n", mkey);
	}
	else
	{
		ft_printf("mouse - other key pressed\n");
	}
	return (0);
}

void	do_mlx_stuff(t_mlx *d)
{
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "FDF");
	if (!d->win)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
		free_stuff(d->map);
		return ;
	}
	d->img.img_p = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	d->img.img_px_p = mlx_get_data_addr(d->img.img_p, &d->img.bits_per_px, &d->img.line_len, &d->img.endian);

	//mlx_mouse_hook(d->win, mouse_hook, d);
	mlx_key_hook(d->win, handle_input, d);

	mlx_loop(d->mlx);
}

int	main(int ac, char **av)
{
	t_map	map;
	t_mlx	d;

	if (ac < 2 || ac > 2 || (ac == 2 && !av[1][0]))
	{
		ft_printf("Error! Do you have a file? (1)\n");
		return (1);
	}
	if (ac == 2)
	{
		init_map_vars(&map);
		get_map(&map, av[1], &d);
		if (map.get_map_ok == TRUE)
			do_mlx_stuff(&d);
		free_stuff(&map);
		ft_printf("_______________________________________________________\n");
	}
	return (0);
}
