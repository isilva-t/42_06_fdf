/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   95_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:24:18 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/08 12:12:25 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_iterator	set_i(int n)
{
	t_iterator	i;

	i.x = n;
	i.y = n;
	return (i);
}

int	get_rgb_color(t_ln_pt *data)
{
	int	color;

	color = ((data->actual_red << 16)
			| (data->actual_green << 8)
			| data->actual_blue);
	return (color);
}

void	is_the_point_inside_window(t_map *map, t_pt pt)
{
	if (pt.x >= WIDTH || pt.y >= HEIGHT)
		map->have_error = TRUE;
}
