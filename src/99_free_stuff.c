/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_free_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:53:24 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/20 16:17:05 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_stuff(t_map *map)
{
	if (map->get_map_ok == TRUE
		|| (map->get_map_ok == FALSE && map->have_error == TRUE))
	{
		while (map->height >= 0)
		{
			free (map->pt[map->height--]);
		}
		free (map->pt);
		free (map->width);
	}
}
