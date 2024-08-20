/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_set_limits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:30:29 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/20 16:56:29 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		set_min_and_max_xy(t_map *map);
void		get_max_width(t_map *map);
static void	init_min_and_max_cords(t_map *map);

void	set_min_and_max_xy(t_map *map)
{
	t_iterator	i;

	if (!map || !map->pt || !map->pt[0] || map->have_error == TRUE)
		return ;
	init_min_and_max_cords(map);
	i.y = -1;
	while (++i.y < map->height)
	{
		i.x = -1;
		while (++i.x < map->width[i.y])
		{
			if (map->pt[i.y][i.x].x < map->min_x.x)
				map->min_x = map->pt[i.y][i.x];
			if (map->pt[i.y][i.x].x > map->max_x.x)
				map->max_x = map->pt[i.y][i.x];
			if (map->pt[i.y][i.x].y < map->min_y.y)
				map->min_y = map->pt[i.y][i.x];
			if (map->pt[i.y][i.x].y > map->max_y.y)
				map->max_y = map->pt[i.y][i.x];
			if (map->pt[i.y][i.x].z < map->min_z.z)
				map->min_z = map->pt[i.y][i.x];
			if (map->pt[i.y][i.x].z > map->max_z.z)
				map->max_z = map->pt[i.y][i.x];
		}
	}
}

void	get_max_width(t_map *map)
{
	int	i;

	i = 0;
	if (!map || !map->width || map->have_error == TRUE)
		return ;
	map->max_width = map->width[0];
	while (++i < map->height)
		if (map->width[i] > map->max_width)
			map->max_width = map->width[i];
}

static void	init_min_and_max_cords(t_map *map)
{
	if (!map || !map->pt[0])
		return ;
	map->max_x = map->pt[0][0];
	map->max_y = map->pt[0][0];
	map->min_x = map->pt[0][0];
	map->min_y = map->pt[0][0];
	map->min_z = map->pt[0][0];
	map->max_z = map->pt[0][0];
}
