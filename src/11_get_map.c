/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_get_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:46:52 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/20 16:57:15 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		get_map(t_map *map, char *av, t_mlx *d);
static void	get_z(const char *str, t_map *map, int *y, int *x);
static void	get_color(const char *color_str, t_map *map, int *y, int *x);
static void	populate_point(t_map *map, t_iterator *i);
static void	populate_map(t_map *map);

void	get_map(t_map *map, char *av, t_mlx *d)
{
	make_big_str(av, map, "", NULL);
	if (map->have_error == TRUE || !map->big_str || map->fd_lines == 0)
	{
		ft_printf("Error reading file! Please check! (2)\n");
		return ;
	}
	if (map->fd_lines > 0)
		map->width = (int *)ft_calloc(sizeof(int), map->fd_lines);
	map->lines = ft_my_split(map->big_str, '\n', &map->height);
	if (map->big_str)
		free (map->big_str);
	populate_map(map);
	ft_free_split_mem(&map->height, map->lines);
	d->map = map;
	if (map->have_error == FALSE)
		map->get_map_ok = TRUE;
}

static void	get_z(const char *str, t_map *map, int *y, int *x)
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
}

static void	get_color(const char *color_str, t_map *map,
		int *y, int *x)
{
	int	color;

	if (have_color(color_str) == TRUE)
		color = ft_atoi_base(color_str + 2, 16);
	else if (have_color(color_str) == -1)
		color = 0xf000000;
	else
		color = 0xffffff;
	map->pt[*y][*x].color = color;
}

static void	populate_point(t_map *map, t_iterator *i)
{
	i->x_zc = 0;
	map->info_point = ft_my_split(map->points[i->x], ',', &i->x_zc);
	get_z(map->info_point[0], map, &i->y, &i->x);
	if (i->x_zc == 2)
		get_color(map->info_point[1], map, &i->y, &i->x);
	else
		map->pt[i->y][i->x].color = 0xffffff;
	if (map->pt[i->y][i->x].z > INT_MAX - 1
		|| map->pt[i->y][i->x].z < INT_MIN + 1
		|| map->pt[i->y][i->x].color == 0xf000000)
		map->have_error = TRUE;
	ft_free_split_mem(&i->x_zc, map->info_point);
}

static void	populate_map(t_map *map)
{
	t_iterator	i;

	map->have_error = 0;
	if (!map || !map->lines)
		return ;
	map->pt = (t_pt **)ft_calloc(sizeof(t_pt *), map->height + 1);
	i.y = -1;
	while (map->lines[++i.y])
	{
		map->width[i.y] = 0;
		map->points = ft_my_split(map->lines[i.y], ' ', &map->width[i.y]);
		map->pt[i.y] = (t_pt *)ft_calloc(sizeof(t_pt), map->width[i.y] + 1);
		i.x = -1;
		while (map->points[++i.x])
			populate_point(map, &i);
		ft_free_split_mem(&i.x, map->points);
	}
	if (map->have_error == TRUE)
		ft_printf("Error! Wrong data in map! (3)\n");
	else
		print_created_map(map, PRINT_COORDS, PRINT_DIMENSIONS);
}
