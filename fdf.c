/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:20:58 by isilva-t          #+#    #+#             */
/*   Updated: 2024/07/11 17:56:17 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*get_big_array(char *av)
{
	int		fd1;
	char	*array;
	char	*line;
	int		i;

	i = -1;
	fd1 = open(av, O_RDONLY);
	if (fd1 == -1)
		return (NULL);
	array = (char *)ft_calloc(1, sizeof(char));
	if (!array)
		return (NULL);
	line = "";
	while (1)
	{
		line = get_next_line(fd1);
		if (!line)
		{
			free (line);
			break;
		}
		ft_strlcpy(array, line, ft_strlen(array) + ft_strlen(line) + 1);
		free (line);
	}
	close(fd1);
	return (array);
}

int	make_map(t_map **map, char **map_points, int y)
{
	int		x;
	long	z;
	int		color;
	int		point_size;
	char	**point;
	t_matrix	*node_to_populate;

	x = 0;
	if (!map || !map_points || !*map_points)
		return (0);
	while (map_points[x] && map_points[x][0] != '\n')
	{
		node_to_populate = append_node(map, x, y);
		if (!node_to_populate)
			return (0);
		point_size = ft_count_words(map_points[x], ',');
		point = ft_my_split(map_points[x++], ',', point_size);
		z = get_z(point[0]);
		if (point[1])
			color = get_color(point[1]);
		else
			color = 0xffffff;
		ft_free_split_mem(point_size, point);
		if (z < INT_MIN || z > INT_MAX || color == 0xf000000)
		{
			free_list(map);
			return (0);
		}
		node_to_populate->z = z;
		node_to_populate->color = color;
	}
	return (1);
}

int	main(int ac, char **av)
{
	char	*big_array;
	char	**map_points;
	int		n_points;
	int		y;
	int		map_created;
	t_map	*map;

	map = NULL;
	n_points = 0;
	if (ac < 2 || ac > 2 || (ac == 2 && !av[1][0]))
	{
		ft_printf("Invalid file! (1)\n");
		return (1);
	}
	if (ac == 2)
	{
		map_created = 1;
		/*y = -1;
		y_lines = get_y_lines_and_valid_map(0, av[1]);
		if (y_lines == -1)
		{
			ft_printf("Invalid map! Please check it! (2)\n");
			return (0);
		}*/
		big_array = get_big_array(av[1]);
		if (!big_array)
		{
			ft_printf("Invalid file (3)\n");
			return (0);
		}
		/*
		map_points = ft_my_split(first_matrix[y], ' ', n_points);
		map_created = make_map(&map, map_points, y);
		ft_free_split_mem(n_points, map_points);
		//print_list(&map);
		if (map_created == 0)
			ft_printf("Invalid map! Please check it! (4)\n");
		ft_free_split_mem(y_lines, first_matrix);	
		free_list(&map);*/
		ft_printf("______________________________________________\n");
	}
	return (0);
}
