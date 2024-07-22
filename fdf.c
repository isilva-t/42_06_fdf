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

typedef struct s_lst
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	int		sum_x;
	int		sum_y;
}			t_lst;

void free_mlx(t_lst *d)
{
	mlx_destroy_window(d->mlx, d->win);
	mlx_destroy_display(d->mlx);
	free(d->mlx);
	exit(1);
}

int	handle_input(int keysym, t_lst *d)
{
	if (keysym == XK_Escape)
		free_mlx(d);
	return (0);
}

int	main(int ac, char **av)
{
	t_map	map;
	t_lst	d;

	if (ac < 2 || ac > 2 || (ac == 2 && !av[1][0]))
	{
		ft_printf("Error! Do you have a file? (1)\n");
		return (1);
	}
	if (ac == 2)
	{
		init_map_vars(&map);
		get_map(&map, av[1]);

		d.mlx = mlx_init();
		d.win = mlx_new_window(d.mlx, 400, 400, "FDF");
		if (!d.win)
		{
			mlx_destroy_display(d.mlx);
			free(d.mlx);
			free_stuff(&map);
			return (1);
		}
		d.x = 0;
		d.y = 0;
		d.sum_x = 1;
		d.sum_y = 1;

while (d.y + d.sum_y < 400)
	{
		d.x = 0;
		while (d.x + d.sum_x < 400)
		{
			mlx_pixel_put(d.mlx,
					   d.win,
					   d.x + d.sum_x,
					d.y + d.sum_y,
			   	rand() % 0xf8f8f8);
			d.x += 12;
			if (d.x > 385)
				d.sum_x -= 1;
			if (d.sum_x == 0)
				d.sum_x = 10;
		}
		d.y += 3;
	}

	mlx_key_hook(d.win, handle_input, &d);

	mlx_loop(d.mlx);
	//free (d.mlx);
	free_stuff(&map);
	ft_printf("_______________________________________________________\n");
	}
	return (0);
}
