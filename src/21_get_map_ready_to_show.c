/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_get_map_ready_to_show.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:44:51 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/20 16:55:14 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		get_map_ready_to_show(t_map *map);
static void	set_offset_p2p(t_map *map);
static void	apply_offset_p2p(t_map *map);
static void	apply_isometric(t_map *map);
static void	center_map(t_map *map);

void	get_map_ready_to_show(t_map *map)
{
	if (map->get_map_ok == FALSE)
		return ;
	set_offset_p2p(map);
	apply_offset_p2p(map);
	apply_isometric(map);
	center_map(map);
}

static void	set_offset_p2p(t_map *map)
{
	int	offset_p2p_x;
	int	offset_p2p_y;

	get_max_width(map);
	set_min_and_max_xy(map);
	offset_p2p_y = abs((int)map->max_z.z - (int)map->min_z.z);
	if (HEIGHT > offset_p2p_y)
		offset_p2p_y = HEIGHT;
	if (!map || map->have_error == TRUE)
		return ;
	if (map->width[0] > 1)
		offset_p2p_x = ((WIDTH - 1) / (map->max_width - 1));
	else
		offset_p2p_x = WIDTH - X_BORDER;
	if (map->height > 1)
		offset_p2p_y /= (map->height - 1);
	else
		offset_p2p_y -= Y_BORDER;
	if (offset_p2p_x < offset_p2p_y)
		map->offset_p2p = (offset_p2p_x / 1.5);
	else
		map->offset_p2p = (offset_p2p_y / 1.5);
	if (map->offset_p2p < 1)
		map->offset_p2p = 1;
}

static void	apply_offset_p2p(t_map *map)
{
	t_iterator	i;

	if (!map || !map->pt || !map->pt[0] || map->have_error == TRUE)
		return ;
	i.y = -1;
	while (++i.y < map->height)
	{
		i.x = -1;
		while (++i.x <= map->width[i.y])
		{
			map->pt[i.y][i.x].x += (map->offset_p2p * i.x);
			map->pt[i.y][i.x].y += (map->offset_p2p * i.y);
		}
	}
}

static void	apply_isometric(t_map *map)
{
	t_iterator	i;
	int			tmp;

	if (!map || !map->pt || !map->pt[0] || map->have_error == TRUE)
		return ;
	i.y = -1;
	while (++i.y < map->height)
	{
		i.x = -1;
		while (++i.x <= map->width[i.y])
		{
			tmp = map->pt[i.y][i.x].x;
			map->pt[i.y][i.x].x = (tmp - map->pt[i.y][i.x].y)
				* cos(0.523599);
			map->pt[i.y][i.x].y = (tmp + map->pt[i.y][i.x].y)
				* sin(0.523599) - (map->pt[i.y][i.x].z * Z_FACTOR);
		}
	}
}

static void	center_map(t_map *map)
{
	t_iterator	i;
	int			offset_x;
	int			offset_y;

	if (!map || map->have_error == TRUE)
		return ;
	set_min_and_max_xy(map);
	offset_x = abs(map->max_x.x) - abs(map->min_x.x);
	offset_y = abs(map->max_y.y) - abs(map->min_y.y);
	offset_x = (WIDTH - offset_x) / 2;
	offset_y = (HEIGHT - offset_y) / 2;
	i.y = -1;
	while (++i.y < map->height)
	{
		i.x = -1;
		while (++i.x < map->width[i.y])
		{
			map->pt[i.y][i.x].x += offset_x;
			map->pt[i.y][i.x].y += offset_y;
		}
	}
}
