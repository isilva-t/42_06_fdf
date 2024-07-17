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
#include "libs/libft/libft.h"

void	get_z(const char *str, t_map *map, int *y_size, int *x_size)
{
	long	nbr;
	int		i;

	i = 0;
	nbr = (long)INT_MAX + 3;
	map->pt[*y_size][*x_size].z = nbr;
	if (!str)
		return ;
	if (!(*str == '-' || *str == '+' || ft_isdigit(*str)))
		return ;
	if ((*str == '+' || *str == '-') && !(ft_isdigit(*(str + 1))))
		return ;
	while (str[++i])
	{
		if (str[i] == '\n')
			break ;
		if (!(ft_isdigit(str[i])))
			return ;
	}
	map->pt[*y_size][*x_size].z = ft_atol(str);
	return ;
}

void	get_color(const char *color_str, t_map *map,
		int *y_lines, int *x_lines)
{
	int	color;

	if (have_color(color_str) == 1)
		color = ft_atoi_base(color_str + 2, 16);
	else if (have_color(color_str) == -1)
		color = 0xf000000;
	else
		color = 0xffffff;
	map->pt[*y_lines][*x_lines].color = color;
	return ;
}

int	make_map(char **map_lines, t_map *map)
{
	char		**points;
	char		**info_point;
	t_map_size	map_size;
	int			have_error;

	have_error = 0;
	map_size.y_size = -1;
	if (!map || !map_lines || !*map_lines)
		return (0);
	map->pt = (t_pt **)ft_calloc(sizeof(t_pt *), map->y_lines + 1);
	while (map_lines[++map_size.y_size])
	{
		map->width[map_size.y_size] = 0;
		points = ft_my_split(map_lines[map_size.y_size], ' ', &map->width[map_size.y_size]);
		//ft_printf("map->width[%d] == %d\n", map_size.y_size, map->width[map_size.y_size]);
		map->pt[map_size.y_size] = (t_pt *)ft_calloc(sizeof(t_pt), map->width[map_size.y_size]);
		map_size.i_pt = -1;
		while (points[++map_size.i_pt])
		{
			map_size.j_pt = 0;
			info_point = ft_my_split(points[map_size.i_pt], ',', &map_size.j_pt);
			get_z(info_point[0], map, &map_size.y_size, &map_size.i_pt);
			//ft_printf("z: %d\n", map->pt[map_size.y_size][map_size.i_pt].z);
			if (map_size.j_pt == 2)
				get_color(info_point[1], map, &map_size.y_size, &map_size.i_pt);
			else
				map->pt[map_size.y_size][map_size.i_pt].color = 0xffffff;
			//ft_printf("color: %d\n", map->pt[map_size.y_size][map_size.i_pt].color);
			if (map->pt[map_size.y_size][map_size.i_pt].z < INT_MIN
				|| map->pt[map_size.y_size][map_size.i_pt].z > INT_MAX
				|| map->pt[map_size.y_size][map_size.i_pt].color == 0xf000000)
				have_error = 1;
			ft_free_split_mem(&map_size.j_pt, info_point);
		}
		map_size.x_size = map->width[map_size.y_size];
		ft_free_split_mem(&map_size.x_size, points);
	}
	return (have_error);
}

int	main(int ac, char **av)
{
	char	**map_lines;
	t_map	map;
	int		y_lines_test;

	if (ac < 2 || ac > 2 || (ac == 2 && !av[1][0]))
	{
		ft_printf("Error, please check! (1)\n");
		return (1);
	}
	if (ac == 2)
	{
		map.have_error = 0;
		map.height = 0;
		map.width = 0;
		map.y_lines = 0;
		make_big_array(av[1], &map, "");
		if (!map.big_str)
			ft_printf("Error, please check! (2)\n");
		if (map.height > 0)
			map.width = (int *)ft_calloc(sizeof(int), map.height);
		map_lines = ft_my_split(map.big_str, '\n', &map.y_lines);
		free (map.big_str);
		map.have_error = make_map(map_lines, &map);
		if (map.have_error == 1)
			ft_printf("Error, please check! (3)\n");
		else
		{
			print_created_map(&map, 1);
			ft_printf("\033[0;36m\nmap.width[0]: %d\nmap.height: %d\n\033[0m", map.width[0], map.height);
		}
		/////////////////////////////////////////////
		y_lines_test = map.y_lines;
		ft_free_split_mem(&map.y_lines, map_lines);
		while (y_lines_test >= 0)
			free (map.pt[y_lines_test--]);
		free (map.pt);
		free (map.width);
		/////////////////////////////////////////////
		ft_printf("______________________________________________\n");
	}
	return (0);
}
