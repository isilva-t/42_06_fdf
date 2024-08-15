/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   50_do_mlx_stuff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:16:57 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/08 16:46:02 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	free_mlx(t_mlx *d)
{
	mlx_destroy_image(d->mlx, d->img.img_p);
	mlx_destroy_window(d->mlx, d->win);
	mlx_destroy_display(d->mlx);
	free(d->mlx);
	return (1);
}

void	my_pixel_put(t_img *img, t_iterator *i, t_map *map, int color)
{
	int	offset;

	offset = (img->line_len * map->pt[i->y][i->x].y) + (map->pt[i->y][i->x].x * (img->bits_per_px / 8));

	*((unsigned int *)(offset + img->img_px_p)) = color;
}

void	new_px_put(t_img *img, t_pt pt, int color)
{
	int	offset;

	offset = (img->line_len * pt.y) + (pt.x * (img->bits_per_px / 8));

	*((unsigned int *)(offset + img->img_px_p)) = color;

}

void	set_data_to_draw_line(t_ln_pt *data)
{
	data->x_direction = -1;
	if (data->actual.x < data->next.x)
		data->x_direction = 1;
	data->y_direction = -1;
	if (data->actual.y < data->next.y)
		data->y_direction = 1;
	data->delta_x = abs(data->next.x - data->actual.x);
	data->delta_y = abs(data->next.y - data->actual.y);
	data->err = data->delta_x - data->delta_y;
}

void	draw_line(t_mlx *d, t_iterator i, int x_sum, int y_sum)
{
	t_ln_pt	data;

	data.actual = d->map->pt[i.y + y_sum][i.x];
	data.next = d->map->pt[i.y][i.x + x_sum];
	set_data_to_draw_line(&data);
	new_px_put(&d->img, data.actual, data.actual.color);
	while (data.actual.x != data.next.x || data.actual.y != data.next.y)
	{
		data.e2 = 2 * data.err;
		if (data.e2 > -data.delta_y)
		{
			data.err -= data.delta_y;
			data.actual.x += data.x_direction;
		}
		if (data.e2 < data.delta_x)
		{
			data.err += data.delta_x;
			data.actual.y += data.y_direction;
		}
		new_px_put(&d->img, data.actual, data.actual.color);
	}
}

void	map_to_screen(t_mlx *d, int color)
{
	t_iterator	i;

	color += color - color;
	i.y = 0;
	while (i.y < d->map->height)
	{
		i.x = 0;
		while (i.x < d->map->width[i.y])
		{
			if (i.x < d->map->width[i.y] - 1)
				draw_line(d, i, 1, 0);
			if (i.y < d->map->height - 1 && i.x < d->map->width[i.y + 1])
				draw_line(d, i, 0, 1);
			i.x++;
		}
		i.y++;
	}
}


int	handle_input(int key, t_mlx *d)
{
	if (key == XK_r)
	{
		map_to_screen(d, 0xff0000);
		ft_printf("key %d pressed\n", key);
	}
	else if (key == XK_g)
	{
		map_to_screen(d, 0x00ff00);
		ft_printf("key %d pressed\n", key);
	}
	else if (key == XK_w)
	{
		map_to_screen(d, 0xffffff);
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
/*
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
}*/
//mlx_mouse_hook(d->win, mouse_hook, d);
void	do_mlx_stuff(t_mlx *d)
{
	if (d->map->get_map_ok == FALSE)
		return ;
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
	d->img.img_px_p = mlx_get_data_addr(d->img.img_p,
									 &d->img.bits_per_px,
									 &d->img.line_len,
										&d->img.endian);
	map_to_screen(d, 0xffffff);
	mlx_put_image_to_window(d->mlx, d->win, d->img.img_p, 0, 0);
	mlx_key_hook(d->win, handle_input, d);

	mlx_loop(d->mlx);
}
