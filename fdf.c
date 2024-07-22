/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:20:58 by isilva-t          #+#    #+#             */
/*   Updated: 2024/07/17 17:21:22 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_stuff(t_map *map)
{
	if (map->get_map_ok == TRUE)
	{
		while (map->height >= 0)
			free (map->pt[map->height--]);
		free (map->pt);
		free (map->width);
	}
}

int	main(int ac, char **av)
{
	t_map	map;

	if (ac < 2 || ac > 2 || (ac == 2 && !av[1][0]))
	{
		ft_printf("Error! Do you have a file? (1)\n");
		return (1);
	}
	if (ac == 2)
	{
		init_map_vars(&map);
		get_map(&map, av[1]);
		free_stuff(&map);
		ft_printf("_______________________________________________________\n");
	}
	return (0);
}
