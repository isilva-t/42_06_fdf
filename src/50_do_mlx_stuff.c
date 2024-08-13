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

void	new_px_put(t_img *img, t_iterator actual, int color)
{
	int	offset;

	offset = (img->line_len * actual.y) + (actual.x * (img->bits_per_px / 8));

	*((unsigned int *)(offset + img->img_px_p)) = color;

}

void	draw_horizontal_line(t_mlx *d, t_iterator i)
{
	t_iterator	actual;
	t_iterator	next;
	int	delta_x;
	int	delta_y;
	int	decision;
	actual.x = d->map->pt[i.y][i.x].x;
	actual.y = d->map->pt[i.y][i.x].y;
	next.x = d->map->pt[i.y][i.x + 1].x;
	next.y = d->map->pt[i.y][i.x + 1].y;
	//step1
	delta_x = next.x - actual.x;
	delta_y = next.y - actual.y;
	//step2
	decision = 2 * delta_y - delta_x;
	//step3
	while (actual.x != next.x)
	{
		if (decision > 0)
		{
			decision += (2 * delta_y) - (2 * delta_x);
			actual.x += 1;
			actual.y += 1;
			new_px_put(&d->img, actual, 0xffff00);
		}
		else if (decision <= 0)
		{
			decision += 2 * delta_y;
			actual.x += 1;
			new_px_put(&d->img, actual, 0xffff00);
		}
		//else
		//	break ;
	}
}

void	draw_vertical_line(t_mlx *d, t_iterator i)
{
	t_iterator	actual;
	t_iterator	next;
	int	delta_x;
	int	delta_y;
	int	decision;
	actual.x = d->map->pt[i.y + 1][i.x].x;
	actual.y = d->map->pt[i.y + 1][i.x].y;
	next.x = d->map->pt[i.y][i.x].x;
	next.y = d->map->pt[i.y][i.x].y;
	//step1
	delta_x = next.x - actual.x;
	delta_y = actual.y - next.y;
	//step2
	decision = 2 * delta_y - delta_x;
	//step3
	while (actual.x != next.x || actual.y != next.y)
	{
		if (decision > 0)
		{
			decision += (2 * delta_y) - (2 * delta_x);
			actual.x += 1;
			actual.y -= 1;
			new_px_put(&d->img, actual, 0x00ffff);
		}
		else if (decision <= 0)
		{
			decision += 2 * delta_y;
			actual.x += 1;
			new_px_put(&d->img, actual, 0x00ffff);
		}
		//else
		//	break ;
	}

}


void	map_to_screen(t_mlx *d, int color)
{
	t_iterator	i;

	i.y = -1;
	while (d->map->pt[++i.y])
	{
		i.x = -1;
		while (++i.x < d->map->width[i.y])
		{
			my_pixel_put(&d->img, &i, d->map, color);
		}
	}
	i.y = 0;
	while (d->map->pt[i.y] && i.y < d->map->height)
	{
		i.x = 0;
		while (i.x < d->map->width[i.y])
		{
			if (i.x < d->map->width[i.y] - 1)
				draw_horizontal_line(d, i);
			//if (i.y < d->map->height - 1 && d->map->pt[i.y + 1][i.x].y)
			if (i.y < d->map->height - 1 && i.x < d->map->width[i.y + 1])
				draw_vertical_line(d, i);
			i.x++;
		}
		i.y++;
		//if (i.y == 3)
		//	break ;
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
