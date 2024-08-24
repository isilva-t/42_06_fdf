/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:52:45 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/20 16:54:05 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_line(t_mlx *d, t_iterator i, int x_sum, int y_sum);
static void	my_px_put(t_imgs *img, t_pt pt, int color);
static void	set_delta_color(t_ln_pt *data);
static void	set_color_on_point(t_ln_pt *data);
static void	set_data_to_draw_line(t_ln_pt *data);

void	draw_line(t_mlx *d, t_iterator i, int x_sum, int y_sum)
{
	t_ln_pt	data;

	data.actual = d->map->pt[i.y + y_sum][i.x];
	data.next = d->map->pt[i.y][i.x + x_sum];
	if (is_pt_inside_window(data.actual) == TRUE)
		my_px_put(&d->img, data.actual, data.actual.color);
	set_data_to_draw_line(&data);
	while (data.actual.x != data.next.x || data.actual.y != data.next.y)
	{
		data.e2 = 2 * data.err;
		set_color_on_point(&data);
		if (data.e2 > -data.delta_y)
		{
			data.err -= data.delta_y;
			data.actual.x += data.x_direction;
		}
		if (data.e2 < data.delta_x)
		{
			data.err += data.delta_x;
			data.actual.y += data.y_direction;
		}
		if (is_pt_inside_window(data.actual) == TRUE)
			my_px_put(&d->img, data.actual, data.actual.color);
	}
}

static void	my_px_put(t_imgs *img, t_pt pt, int color)
{
	int	offset;

	offset = (img->line_len * pt.y) + (pt.x * (img->bits_per_px / 8));
	*((unsigned int *)(offset + img->img_px_p)) = color;
}

static void	set_delta_color(t_ln_pt *data)
{
	int	delta_x;
	int	delta_y;

	delta_x = abs(data->next.x - data->actual.x);
	delta_y = abs(data->next.y - data->actual.y);
	if (delta_x >= delta_y)
		data->delta_color = delta_x;
	else
		data->delta_color = delta_y;
}

static void	set_color_on_point(t_ln_pt *data)
{
	data->actual_red = (data->actual.color >> 16) & 0xFF;
	data->actual_green = (data->actual.color >> 8) & 0xFF;
	data->actual_blue = data->actual.color & 0xFF;
	data->next_red = (data->next.color >> 16) & 0xFF;
	data->next_green = (data->next.color >> 8) & 0xFF;
	data->next_blue = data->next.color & 0xFF;
	set_delta_color(data);
	data->actual_red += ((data->next_red - data->actual_red))
		/ data->delta_color;
	data->actual_green += ((data->next_green - data->actual_green))
		/ data->delta_color;
	data->actual_blue += ((data->next_blue - data->actual_blue))
		/ data->delta_color;
	data->actual.color = get_rgb_color(data);
}

static void	set_data_to_draw_line(t_ln_pt *data)
{
	if (!data)
		return ;
	data->x_direction = -1;
	if (data->actual.x < data->next.x)
		data->x_direction = 1;
	data->y_direction = -1;
	if (data->actual.y < data->next.y)
		data->y_direction = 1;
	data->delta_x = abs(data->next.x - data->actual.x);
	data->delta_y = abs(data->next.y - data->actual.y);
	data->err = data->delta_x - data->delta_y;
}
