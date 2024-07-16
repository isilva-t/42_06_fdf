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
#include <limits.h>


static t_matrix	*ft_matrixlast(t_matrix *lst);

/*
static	t_matrix	*print_line(t_matrix *node)
{
	ft_printf("\033[0;31m %d\033[0;32m%d\033[0m%d\033[0;33m%d\033[0m", 
		   node->x, node->y, node->z, node->color);
	node = node->next;
	return (node);
}

static	void	print_nodes(t_matrix *cur_a, int print)
{
	auto int i = 0;
	if (!cur_a || print == 0)
		return ;
	while (cur_a)
	{
		if (cur_a && cur_a->x == 0)
		{
			ft_printf("\n");
			i++;
		}
		if (cur_a)
			cur_a = print_line(cur_a);
	}
	ft_printf("\n");
}

void	print_list(t_matrix **a)
{
	auto t_matrix * cur_prev_a = NULL;
	auto t_matrix * cur_a = NULL;;
	if (a && *a)
	{
		cur_a = *a;
		cur_prev_a = *a;
		cur_prev_a = ft_matrixlast(cur_prev_a);
		while (cur_prev_a->prev)
			cur_prev_a = cur_prev_a->prev;
	}
	print_nodes(cur_a, 0);
	print_nodes(cur_prev_a, 0);
}*/

int	get_y_lines_and_valid_map(int y_lines, char *av)
{
	int		fd1;
	char	*line;
	int		len;
	int		last_space;

	len = -1;
	fd1 = open(av, O_RDONLY);
	if (fd1 == -1)
		return (y_lines);
	line = "";
	while (line)
	{
		last_space = 0;
		line = get_next_line(fd1);
		if (!line)
		{
			free (line);
			break;
		}
		if (line[ft_strlen(line) - 2] == ' ')
			last_space = 1;
		if (len == -1)
			len = ft_count_words(line, ' ') - last_space;
		if (ft_count_words(line, ' ') - last_space != len)
			return (free (line), -1);
		free (line);
		y_lines++;
	}
	close(fd1);
	return (y_lines);
}

char	**get_first_matrix(int y_lines, char *av)
{
	int		fd1;
	char	**matrix;
	char	*line;
	int		i;

	i = -1;
	fd1 = open(av, O_RDONLY);
	if (fd1 == -1)
		return (NULL);
	matrix = (char **)ft_calloc(y_lines + 1, sizeof(char *));
	if (!matrix)
		return (NULL);
	line = "";
	while (++i < y_lines)
	{
		line = get_next_line(fd1);
		if (!line)
		{
			free (line);
			break;
		}
		matrix[i] = ft_calloc((ft_strlen(line) + 1), sizeof(char *));
		if (!matrix[i])
			return (free (line), NULL);
		ft_strlcpy(matrix[i], line, ft_strlen(line) + 1);
		free (line);
	}
	close(fd1);
	return (matrix);
}

int	ft_matrixsize(t_matrix *lst)
{
	int		size;
	t_matrix	*counter;

	size = 0;
	counter = (t_matrix *)lst;
	while (counter)
	{
		size++;
		counter = counter->next;
	}
	return (size);
}

static t_matrix	*ft_matrixlast(t_matrix *lst)
{
	t_matrix	*last;
	int		size;

	last = (t_matrix *)lst;
	size = ft_matrixsize(lst);
	while (size > 1)
	{
		last = last->next;
		size--;
	}
	return (last);
}

static t_matrix	*append_node(t_matrix **map, int x, int y)
{
	t_matrix	*new_node;
	t_matrix	*last_node;

	if (!map)
		return (NULL);
	new_node = malloc(sizeof(t_matrix) + 1);
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->x = x;
	new_node->y = y;
	if (!(*map))
	{
		new_node->prev = NULL;
		*map = new_node;
	}
	else
	{
		last_node = (t_matrix *)ft_matrixlast(*map);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	last_node = ft_matrixlast(*map);
	return (last_node);
}

static long	get_z(char *str)
{
	long	nbr;
	int		i;

	i = 0;
	nbr = (long)INT_MAX + 3;
	if (!str)
		return (nbr);
	if (!(*str == '-' || *str == '+' || ft_isdigit(*str)))
		return (nbr);
	if ((*str == '+' || *str == '-') && !(ft_isdigit(*(str + 1))))
		return (nbr);
	while (str[++i])
	{
		if (str[i] == '\n')
			break;
		if (!(ft_isdigit(str[i])))
			return (nbr);
	}
	nbr = ft_atol(str);
	return (nbr);
}
///////////////////////////// COLOR MAKE
static int	have_color(const char *str)
{
	int	i;

	i = 2;
	if (!str)
		return (0);
	if (ft_strlen(str) < 8 || ft_strlen(str) > 9 
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

int	get_color(const char	*color_str)
{
	int	color;
	
	if (have_color(color_str) == 1)
		color = ft_atoi_base(color_str + 2, 16);
	else if (have_color(color_str) == -1)
		color = 0xf000000;
	else
		color = 0xffffff;
	return (color);
}
//////////////////////////////////HANDLE ERROR
void	free_list(t_matrix **stack)
{
	t_matrix	*tmp;
	t_matrix	*current;

	if (!*stack)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*stack = NULL;
	stack = NULL;
}

int	make_map(t_matrix **map, char **map_points, int y)
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
//printf("z = %zu, color =  %d\n", z, color);
			free_list(map);
			return (0);
		}
		node_to_populate->z = z;
		node_to_populate->color = color;
	}
	return (1);
}

void	make_loweralpha_array(char	*str)
{
	while (str)
	{
		*str = ft_tolower(*str);
		str++;
	}
}

int	main(int ac, char **av)
{
	int		y_lines;
//	int		x_lines;
	char	**first_matrix;
	//char	*map_array;
	char	**map_points;
	int		n_points;
	int		y;
	int		map_created;
	t_matrix	*map;

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
		y = -1;
		y_lines = get_y_lines_and_valid_map(0, av[1]);
		if (y_lines == -1)
		{
			ft_printf("Invalid map! Please check it! (2)\n");
			return (0);
		}
		first_matrix = get_first_matrix(y_lines, av[1]);
		if (!first_matrix)
		{
			ft_printf("Invalid file (3)\n");
			return (0);
		}
		while (first_matrix[++y] && map_created == 1)
		{
			n_points = ft_count_words(first_matrix[y], ' ');
			map_points = ft_my_split(first_matrix[y], ' ', n_points);
			map_created = make_map(&map, map_points, y);
			ft_free_split_mem(n_points, map_points);
		}
		//print_list(&map);
		if (map_created == 0)
			ft_printf("Invalid map! Please check it! (4)\n");
		ft_free_split_mem(y_lines, first_matrix);	
		free_list(&map);
		ft_printf("______________________________________________\n");
	}
	return (0);
}
