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

void	set_z_factor(t_map *map)
{
	int	diagonal_power_2;
	int	tmp;

	diagonal_power_2 = (map->max_width * map->max_width)
				+ (map->height * map->height);
	tmp = 1;
	while (tmp * tmp < diagonal_power_2)
	{
		tmp++;
		if (tmp * tmp >= diagonal_power_2)
		{
			tmp--;
			break ;
		}
	}
	map->z_factor = (abs(((int)map->max_z.z - (int)map->min_z.z)));
	if (map->z_factor * map->z_factor <= tmp * 2)
	{
		ft_printf("a\n");
		map->z_factor = 0.4;
	}
	else if (map->z_factor * 2 <= tmp * tmp)
	{
		ft_printf("b\n");
		map->z_factor = 0.3;
	}
	else if (map->z_factor * 2 <= tmp * tmp)
	{
		ft_printf("c\n");
		map->z_factor = 0.1;
	}
	else
	{
		ft_printf("d\n");
		map->z_factor = 1;
	}

	ft_printf("tmp %d max %d min %d \n", tmp, map->max_z.z, map->min_z.z);
}

static void	set_offset_p2p(t_map *map)
{
	float	offset_p2p_x;
	float	offset_p2p_y;

	get_max_width(map);
	set_min_and_max_xy(map);
	set_z_factor(map);
	//if (HEIGHT > offset_p2p_y)
	//	offset_p2p_y = HEIGHT;
	if (!map || map->have_error == TRUE)
		return ;
	if (map->width[0] > 1)
		offset_p2p_x = ((float)(WIDTH - 1) / (map->max_width - 1));
	else
		offset_p2p_x = WIDTH - X_BORDER;
	if (map->height > 1)
		offset_p2p_y = ((float)HEIGHT / (map->height - 1));
	else
		offset_p2p_y = HEIGHT - Y_BORDER * 2;
	if (offset_p2p_x < offset_p2p_y)
		map->offset_p2p = (offset_p2p_x / 1.5);
	else
		map->offset_p2p = (offset_p2p_y / 1.5);
	//if (map->offset_p2p < 1)
	//	map->offset_p2p = 1;
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
			map->pt[i.y][i.x].y = ((tmp + map->pt[i.y][i.x].y)
				* sin(0.523599) - (map->pt[i.y][i.x].z) * map->z_factor);
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
