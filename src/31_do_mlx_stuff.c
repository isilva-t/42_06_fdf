/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_do_mlx_stuff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:16:57 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/20 16:58:54 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			do_mlx_stuff_and_show_map(t_mlx *d, t_map *map);
static int		free_mlx(t_mlx *d);
static int		clean_exit(t_mlx *d);
static void		map_to_mlx_array(t_mlx *d);
static int		handle_input(int key, t_mlx *d);

void	do_mlx_stuff_and_show_map(t_mlx *d, t_map *map)
{
	if (map->get_map_ok == FALSE || map->have_error == TRUE || map->fd1 < 1)
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
	map_to_mlx_array(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img.img_p, 0, 0);
	mlx_key_hook(d->win, handle_input, d);
	mlx_hook(d->win, DestroyNotify, 0L, &clean_exit, d);
	mlx_string_put(d->mlx, d->win, WIDTH - 160, 20, 0xFFFFFF,
		"Press \"Esc\" key to exit.");
	mlx_loop(d->mlx);
}

static int	free_mlx(t_mlx *d)
{
	mlx_destroy_image(d->mlx, d->img.img_p);
	mlx_destroy_window(d->mlx, d->win);
	mlx_destroy_display(d->mlx);
	free(d->mlx);
	return (1);
}

static int	clean_exit(t_mlx *d)
{
	free_stuff(d->map);
	exit(free_mlx(d));
}

static void	map_to_mlx_array(t_mlx *d)
{
	t_iterator	i;

	if (only_have_white(d->map) == TRUE)
		set_color_based_on_z(d->map);
	i = set_i(0);
	if (d->map->height == 1 && d->map->width[0] == 1)
		draw_line(d, i, 0, 0);
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

static int	handle_input(int key, t_mlx *d)
{
	if (key == XK_Escape)
	{
		printf("key %d (ESC) pressed. Program quit\n\n", key);
		clean_exit(d);
	}
	return (0);
}
