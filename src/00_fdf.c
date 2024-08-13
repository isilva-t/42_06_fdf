/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:20:58 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/08 18:18:30 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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

	offset_p2p_x = WIDTH / (map->max_width - 1);
	offset_p2p_y = HEIGHT / (map->height - 1);
	if (offset_p2p_x < 5 || offset_p2p_y < 5)
		map->have_error = TRUE;
	if (offset_p2p_x < offset_p2p_y)
		map->offset_p2p = (offset_p2p_x / 1.5);
	else
		map->offset_p2p = (offset_p2p_y / 1.5);
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

void	apply_isometric(t_map *map)
{
	t_iterator i;
	int		tmp;

	if (!map || map->have_error ==TRUE)
		return ;
	i.y = -1;
	while (++i.y < map->height)
	{
		i.x = -1;
		while (++i.x <= map->width[i.y])
		{
			tmp = map->pt[i.y][i.x].x;
			map->pt[i.y][i.x].x = (tmp - map->pt[i.y][i.x].y) * cos(0.523599);
			map->pt[i.y][i.x].y = (tmp + map->pt[i.y][i.x].y) * sin(0.523599) - (map->pt[i.y][i.x].z * 1);
		}
	}
}

void	center_map(t_map *map)
{
	t_iterator i;
	int		offset_x;
	int		offset_y;

	if (!map || map->have_error ==TRUE)
		return ;
	offset_x = abs(map->pt[0][map->width[0]].x) - abs(map->pt[map->height - 1][0].x);
	//offset_y = 
	offset_x = (WIDTH - offset_x) / 2;
	offset_y = ((HEIGHT - (abs(map->pt[map->height - 1][map->width[map->height - 1]].y) - abs(map->pt[0][0].y))) / 2);
	i.y = -1;
	while (++i.y < map->height)
	{
		i.x = -1;
		while (++i.x <= map->width[i.y])
		{
			map->pt[i.y][i.x].x += offset_x;
			map->pt[i.y][i.x].y += offset_y;
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
		apply_isometric(&map);
		center_map(&map);

		if (map.get_map_ok == TRUE)
		{
			do_mlx_stuff(&d);
		}
		free_stuff(&map);
		ft_printf("_______________________________________________________\n");
	}
	return (0);
}
