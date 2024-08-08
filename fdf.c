/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:20:58 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/08 16:02:59 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_max_width(t_map *map)
{
	int	i;

	i = 0;
	if (!map || !map->width)
		return ;
	map->max_width = map->width[0];
	while (++i < map->height)
		if (map->width[i] > map->max_width)
			map->max_width = map->width[i];
}

void	set_offset_p2p(t_map *map)
{
	int	offset_p2p_x;
	int	offset_p2p_y;

ft_printf("\nmax_width: %d\n", map->max_width);
ft_printf("height: %d\n", map->height);

	offset_p2p_x = WIDTH / (map->max_width - 1);
	offset_p2p_y = HEIGHT / (map->height - 1);

ft_printf("offset_p2p_x = %d\n", offset_p2p_x);
ft_printf("offset_p2p_y = %d\n", offset_p2p_y);
	if (offset_p2p_x < 5 || offset_p2p_y < 5)
		map->have_error = TRUE;


	if (offset_p2p_x < offset_p2p_y)
		map->offset_p2p = (offset_p2p_x / 1.5);
	else
		map->offset_p2p = (offset_p2p_y / 1.5);


ft_printf("\nmap_offset_p2p = %d\n\n", map->offset_p2p);
}

void	apply_offset_p2p(t_map *map)
{
	t_iterator	i;

	if (!map || map->have_error ==TRUE)
		return ;
	i.y = -1;
	while (++i.y < map->height)
	{
		i.x = -1;
		while (++i.x <= map->width[i.y])
		{
			map->pt[i.y][i.x].x += map->offset_p2p * i.x;
			map->pt[i.y][i.x].y += map->offset_p2p * i.y;
		}
	}
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

		get_max_width(&map);
		set_offset_p2p(&map);
		apply_offset_p2p(&map);


		if (map.get_map_ok == TRUE)
		{


			do_mlx_stuff(&d);
		}
		free_stuff(&map);
		ft_printf("_______________________________________________________\n");
	}
	return (0);
}
