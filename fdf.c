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

void	get_z(const char *str, t_map *map, int *y, int *x)
{
	int		i;

	i = 0;
	map->pt[*y][*x].z = (long)INT_MAX + 3;
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
	map->pt[*y][*x].z = ft_atol(str);
	return ;
}

void	get_color(const char *color_str, t_map *map,
		int *y, int *x)
{
	int	color;

	if (have_color(color_str) == 1)
		color = ft_atoi_base(color_str + 2, 16);
	else if (have_color(color_str) == -1)
		color = 0xf000000;
	else
		color = 0xffffff;
	map->pt[*y][*x].color = color;
	return ;
}

void	populate_point(t_map *map, t_iterator *i)
{
	i->x_zc = 0;
	map->info_point = ft_my_split(map->points[i->x], ',', &i->x_zc);
			get_z(map->info_point[0], map, &i->y, &i->x);
			if (i->x_zc == 2)
				get_color(map->info_point[1], map, &i->y, &i->x);
			else
				map->pt[i->y][i->x].color = 0xffffff;
			if (map->pt[i->y][i->x].z < INT_MIN
				|| map->pt[i->y][i->x].z > INT_MAX
				|| map->pt[i->y][i->x].color == 0xf000000)
				map->have_error = 1;
			ft_free_split_mem(&i->x_zc, map->info_point);

}

int	populate_map(t_map *map)
{
	t_iterator	i;

	map->have_error = 0;
	if (!map || !map->lines)
		return (0);
	map->pt = (t_pt **)ft_calloc(sizeof(t_pt *), map->y_lines + 1);
	i.y = -1;
	while (map->lines[++i.y])
	{
		map->width[i.y] = 0;
		map->points = ft_my_split(map->lines[i.y], ' ', &map->width[i.y]);
		map->pt[i.y] = (t_pt *)ft_calloc(sizeof(t_pt), map->width[i.y]);
		
		i.x = -1;
		while (map->points[++i.x])
		{
			populate_point(map, &i);
/////
			/*
			i.x_zc = 0;
			map->info_point = ft_my_split(map->points[i.x], ',', &i.x_zc);
			get_z(map->info_point[0], map, &i.y, &i.x);
			if (i.x_zc == 2)
				get_color(map->info_point[1], map, &i.y, &i.x);
			else
				map->pt[i.y][i.x].color = 0xffffff;
			if (map->pt[i.y][i.x].z < INT_MIN
				|| map->pt[i.y][i.x].z > INT_MAX
				|| map->pt[i.y][i.x].color == 0xf000000)
				map->have_error = 1;
			ft_free_split_mem(&i.x_zc, map->info_point);*/
	///////////////////
		}

		ft_free_split_mem(&i.x, map->points);
	}
	return (map->have_error);
}

int	main(int ac, char **av)
{
	t_map	map;

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
		map.lines = ft_my_split(map.big_str, '\n', &map.y_lines);
		free (map.big_str);
		map.have_error = populate_map(&map);
		if (map.have_error == 1)
			ft_printf("Error, please check! (3)\n");
		else
		{
			print_created_map(&map, 1);
			ft_printf("\033[0;36m\nmap.width[0]: %d\nmap.height: %d\n\033[0m", map.width[0], map.height);
		}
		/////////////////////////////////////////////
		ft_free_split_mem(&map.y_lines, map.lines);
		while (map.y_lines >= 0)
			free (map.pt[map.y_lines--]);
		free (map.pt);
		free (map.width);
		/////////////////////////////////////////////
		ft_printf("______________________________________________\n");
	}
	return (0);
}
