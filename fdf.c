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

# define BORDER_Y 50
# define BORDER_X 50

t_iterator	set_i(int n)
{
	t_iterator	i;

	i.x = n;
	i.y = n;
	return (i);
}

int	free_mlx(t_mlx *d)
{
	mlx_destroy_image(d->mlx, d->img.img_ptr);
	mlx_destroy_window(d->mlx, d->win);
	mlx_destroy_display(d->mlx);
	free(d->mlx);
	return (1);
}

void	my_pixel_put(t_img *img, t_iterator i, int color)
{
	int	offset;

	offset = (img->line_len * i.y) + (i.x * (img->bits_per_px / 8));

	*((unsigned int *)(offset + img->img_px_ptr)) = color;
}

void	color_screen(t_mlx *d, int color)
{
	t_iterator	i;

	i = set_i(0);
	i.x += BORDER_X;
	i.y += BORDER_Y;
	while (++i.y < SIDE_LEN - BORDER_Y)
	{
		i.x = 0 + BORDER_X;
		while (++i.x < SIDE_LEN - BORDER_X)
		{
			my_pixel_put(&d->img, i, color);
		}
	}
}

int	handle_input(int keysym, t_mlx *d)
{
	if (keysym == XK_r)
		color_screen(d, 0xff0000);
	else if (keysym == XK_g)
		color_screen(d, 0x00ff00);
	else if (keysym == XK_b)
		color_screen(d, 0x0000ff);
	else if (keysym == XK_Escape)
	{
		printf("The %d key (ESC) has been pressed\n\n", keysym);
		free_stuff(d->map);
		exit(free_mlx(d));
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img.img_ptr, 0, 0);
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
		d->img.img_ptr = mlx_new_image(d->mlx, SIDE_LEN, SIDE_LEN);
		d->img.img_px_ptr = mlx_get_data_addr(d->img.img_ptr, &d->img.bits_per_px, &d->img.line_len, &d->img.endian);

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
