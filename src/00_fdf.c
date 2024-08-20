/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:20:58 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/20 16:57:59 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_map	map;
	t_mlx	d;

	if (ac < 2 || ac > 2 || (ac == 2 && !av[1][0]))
	{
		ft_printf("Error. Do you have a file? (1)\n");
		return (1);
	}
	if (ac == 2)
	{
		if (is_fdf_file(av[1]) == TRUE)
		{
			init_map_vars(&map);
			get_map(&map, av[1], &d);
			get_map_ready_to_show(&map);
			do_mlx_stuff_and_show_map(&d, &map);
			free_stuff(&map);
		}
		else
			ft_printf("Error: No \"*.fdf\" file extension\n");
	}
	ft_printf("_______________________________________________________\n");
	return (0);
}
