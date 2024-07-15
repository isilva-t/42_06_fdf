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


typedef struct s_map_size
{
	int	x_size;
	int	y_size;
}			t_map_size;

typedef struct s_matrix
{
	int		x;
	int		y;
	int		z;
	int		color;
	struct s_matrix	*prev;
	struct s_matrix	*next;
}			t_matrix;

int	get_y_lines_and_valid_map(int y_lines, char *av)
{
	int		fd1;
	char	*line;
	int		len;

	len = -1;
	fd1 = open(av, O_RDONLY);
	line = "";
	while (line)
	{
		line = get_next_line(fd1);
		if (!line)
		{
			free (line);
			break;
		}
		if (len == -1)
			len = ft_count_words(line, ' ');
		if (ft_count_words(line, ' ') != len)
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
	matrix = (char **)malloc(sizeof(char *) * (y_lines + 1));
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
		matrix[i] = malloc(sizeof(char *) * (ft_strlen(line) + 1));
		if (!matrix[i])
			return (free(line), NULL);
		ft_strlcpy(matrix[i], line, ft_strlen(line) + 1);
		free (line);
	}
	close(fd1);
	return (matrix);
}
/*
char	*get_map_array(char **first_matrix, int y_lines)
{
	char	*map_array;
	char	*temp;
	int		i;

	i = -1;
	map_array = ft_strdup("");;
	while (++i < y_lines)
	{
		temp = map_array;
		map_array = ft_strjoin(map_array, first_matrix[i]);
		free (temp);
	}
	return (map_array);
}
*/
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

	i = 1;
	if (!str)
		return (0);
	if (ft_strlen(str) != 8)
		return (-1);
	if (!(*str == '0' && (*(str + 1) == 'x')))
		return (-1);
	while (str[++i])
	{
		if (!(ft_isdigit(str[i]) || (str[i] >= 'a' && str[i] <= 'f')))
			return (-1);
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

int	make_map(t_matrix **map, char **map_points)
{
	int		i;
	int		x;
	int		y;
	long	z;
	int		color;
	int		point_size;
	char	**point;
	t_matrix	*node_to_populate;

	i = -1;
	y = 0;
	x = 0;
	if (!map || !map_points || !*map_points)
		return (0);
	while (map_points[++i])
	{
		node_to_populate = append_node(map, x, y);
		if (!node_to_populate)
			return (0);
		point_size = ft_count_words(map_points[i], ',');
		point = ft_my_split(map_points[i], ',', point_size);
		z = get_z(point[0]);
		if (point[1])
			color = get_color(point[1]);
		else
			color = 0xffffff;
		ft_free_split_mem(point_size, point);
		if (z < INT_MIN || z > INT_MAX || color == 0xf000000)
		{
			printf("z = %zu, color =  %d\n", z, color);
			free_list(map);
			return (0);
		}
		node_to_populate->z = z;
		node_to_populate->color = color;
		x++;
	}
	ft_printf("created line of nodes. See print below\n");
	return (1);
}
/*
void	create_struct_map(t_matrix **map, char	**map_points)
{
	int		i;

	i = 0;

	// need to verify syntax of my string to ensure I can create a list.
	// after this fuction, I need to count nodes to ensure my map is valid again.
	// if not, I need to free the stack created (need to copy free_stack from push_swap)
	while (map_points[i])
		append_node(map, map_points[i])
	point_data = ft_my_split(map_points, ',', data_size)
	
	

	return (map_points);
}*/

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
	int		x_lines;
	char	**first_matrix;
	//char	*map_array;
	char	**map_points;
	int		n_points;
	int		i;
	int		j;
	int		map_created;
	t_matrix	*map;

	map = NULL;
	n_points = 0;
	j = -1;
	if (ac < 2)
		return (1);
	map_created = 1;
	i = -1;
	y_lines = get_y_lines_and_valid_map(0, av[1]);
	if (y_lines == -1)
	{
		ft_printf("The map isn't valid!\n");
		return (0);
	}

	first_matrix = get_first_matrix(y_lines, av[1]);
	x_lines = ft_count_words(first_matrix[0], ' ');
	
	while (first_matrix[++i] && map_created == 1)
	{
		j = -1;
		n_points = ft_count_words(first_matrix[i], ' ');
		map_points = ft_my_split(first_matrix[i], ' ', n_points);
		map_created = make_map(&map, map_points);
		while(map_points[++j])
			ft_printf("%s ", map_points[j]);
		ft_free_split_mem(n_points, map_points);
	}
	if (map_created == 0)
		ft_printf("Error creating map. Please check it.\n\n");

	//have a warning in valgrind below
	ft_free_split_mem(y_lines, first_matrix);	
	////////////////////////////////////////////////////
	free_list(&map);
	ft_printf("\nx_lines: %d_______ y_lines: %d\n", x_lines, y_lines);
	ft_printf("______________________________________________\n");
	return (0);
}
