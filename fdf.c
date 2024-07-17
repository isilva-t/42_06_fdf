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
#include "libs/libft/libft.h"

int	have_color(const char *str)
{
	int	i;

	i = 2;
	if (!str)
		return (0);
	if (ft_strlen(str) > 9 
		|| (ft_strlen(str) == 9 && str[8] != '\n'))
		return (-1);
	if (!(*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')))
		return (-1);
	while (str[i] && i < 8)
	{
		if (!(ft_isdigit(str[i]) 
			|| (str[i] >= 'a' && str[i] <= 'f')
			|| (str[i] >= 'A' && str[i] <= 'F')))
			return (-1);
		i++;
	}
	return (1);
}

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
			break;
		if (!(ft_isdigit(str[i])))
			return ;
	}
	map->pt[*y_size][*x_size].z = ft_atol(str);
		return ;
}

void	get_color(const char	*color_str, t_map *map, int	*y_lines, int *x_lines)
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
	char	**points;
	char	**info_point;
	t_map_size	map_size;
	int	have_error;
	
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
			
			if ( map->pt[map_size.y_size][map_size.i_pt].z < INT_MIN
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

static char	*get_big_array(char *av, int *height)
{
	int		fd1;
	char	*array;
	char	*tmp;
	char	*line;

	fd1 = open(av, O_RDONLY);
	if (fd1 == -1)
		return (NULL);
	array = (char *)ft_calloc(1, sizeof(char) + 1);
	if (!array)
		return (NULL);
	line = "";
	while (line)
	{
		line = get_next_line(fd1);
		if (!line)
		{
			free (line);
			break;
		}
		tmp = array;
		array = ft_strjoin(array, line);
		free (tmp);
		free (line);
		*height += 1;
	}
	close(fd1);
	return (array);
}

static	void	print_created_map(t_map *map, int i)
{
	int	y = 0;
	int	x = 0;
	while (y < map->height && i == 1)
	{
		ft_printf("\n");
		x = 0;
		while (x < map->width[y])
		{
			ft_printf("\033[0m%d\033[0;33m%d\033[0m ", map->pt[y][x].z, map->pt[y][x].color);
			x++;
		}
		y++;
	}
	return ;
}

int	main(int ac, char **av)
{
	char	*big_array;
	char	**map_lines;
	t_map	map;
	int		have_error;
	int	y_lines_test;

	have_error = 0;
	big_array = "";
	//map_points = (char **)ft_calloc(1, sizeof(char *) + 1);
	if (ac < 2 || ac > 2 || (ac == 2 && !av[1][0]))
	{
		ft_printf("Error, please check! (1)\n");
		return (1);
	}
	if (ac == 2)
	{
		/*
		map = (t_map *)ft_calloc(1, sizeof(t_map) + 1);
		if (!map)
			return (1);*/
		map.height = 0;
		map.width = 0;
		map.y_lines = 0;
		big_array = get_big_array(av[1], &map.height);
		if (!big_array)
			ft_printf("Error, please check! (2)\n");
		if (map.height > 0)
			map.width = (int *)ft_calloc(sizeof(int), map.height);
//		ft_printf("big_array:\n%s\n", big_array);
		map_lines = ft_my_split(big_array, '\n', &map.y_lines);
		free (big_array);
		
		have_error = make_map(map_lines, &map);
		if (have_error == 1)
			ft_printf("Error, please check! (3)\n");
		else
		{
			print_created_map(&map, 0);
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
