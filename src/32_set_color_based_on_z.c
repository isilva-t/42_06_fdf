/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   32_set_color_based_on_z.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:52:22 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/20 16:54:38 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		set_color_based_on_z(t_map *map);
static void	set_min_and_max_z_color(t_ln_pt *data);
static void	set_color_on_points(t_map *map, t_ln_pt *data);
static void	set_color_limits(t_ln_pt *data);

void	set_color_based_on_z(t_map *map)
{
	t_ln_pt	data;

	data.min_z = map->min_z;
	data.max_z = map->max_z;
	set_color_limits(&data);
	data.delta_z = abs((int)data.max_z.z - (int)data.min_z.z);
	if (data.delta_z > 255)
		data.delta_z = 255;
	set_min_and_max_z_color(&data);
	set_color_on_points(map, &data);
}

static void	set_min_and_max_z_color(t_ln_pt *data)
{
	if (!data)
		return ;
	data->min_red = (data->min_z.color >> 16) & 0xFF;
	data->min_green = (data->min_z.color >> 8) & 0xFF;
	data->min_blue = data->min_z.color & 0xFF;
	data->max_red = (data->max_z.color >> 16) & 0xFF;
	data->max_green = (data->max_z.color >> 8) & 0xFF;
	data->max_blue = data->max_z.color & 0xFF;
}

static void	set_color_on_points(t_map *map, t_ln_pt *data)
{
	t_iterator	i;
	int			z_fact;

	if (data->min_z.z == data->max_z.z)
		return ;
	data->step_red = ((data->max_red - data->min_red) / data->delta_z);
	data->step_green = ((data->max_green - data->min_green) / data->delta_z);
	data->step_blue = ((data->max_blue - data->min_blue) / data->delta_z);
	i.y = 0;
	while (i.y < map->height)
	{
		i.x = 0;
		while (i.x < map->width[i.y])
		{
			z_fact = ((int)map->pt[i.y][i.x].z - (int)data->min_z.z);
			data->actual_red = data->min_red + (z_fact * data->step_red);
			data->actual_green = data->min_green + (z_fact * data->step_green);
			data->actual_blue = data->min_blue + (z_fact * data->step_blue);
			data->actual.color = get_rgb_color(data);
			map->pt[i.y][i.x].color = data->actual.color;
			i.x++;
		}
		i.y++;
	}
}

static void	set_color_limits(t_ln_pt *data)
{
	if (!data)
		return ;
	if (data->min_z.z < 0)
		data->min_z.color = 0xff0000;
	else if (data->min_z.z == 0)
		data->min_z.color = 0xffffff;
	else
		data->min_z.color = 0xaa5500;
	if (data->max_z.z > 0)
		data->max_z.color = 0x00ffff;
	else if (data->max_z.z == 0)
		data->max_z.color = 0xffffff;
	else
		data->max_z.color = 0x00aa55;
}
