#include "../fdf.h"

static void	set_z_min_and_max(t_map *map, t_ln_pt *data)
{
	t_iterator	i;

	map->max_z = map->pt[0][0];
	map->min_z = map->pt[0][0];
	i.y = -1;
	while (++i.y < map->height)
	{
		i.x = -1;
		while (++i.x <= map->width[i.y])
		{
			if (map->pt[i.y][i.x].z > map->max_z.z)
				map->max_z = map->pt[i.y][i.x];
			if (map->pt[i.y][i.x].z < map->min_z.z)
				map->min_z = map->pt[i.y][i.x];
		}
	}
	data->min_z = map->min_z;
	data->max_z = map->max_z;
	ft_printf("map_min_z.z %d\n", map->min_z.z);
	ft_printf("map_max_z.z %d\n", map->max_z.z);
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

void	set_color_z_based(t_map *map, t_ln_pt *data)
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
			z_fact = map->pt[i.y][i.x].z - data->min_z.z;
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

void	set_color_based_on_z(t_map *map)
{
	t_ln_pt	data;
	set_z_min_and_max(map, &data);
	set_color_limits(&data);
	data.delta_z = abs((int)data.max_z.z - (int)data.min_z.z);
	set_min_and_max_z_color(&data);
	set_color_z_based(map, &data);
}
