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
		ft_printf("%s", matrix[i]);
		free (line);
	}
	close(fd1);
	return (matrix);
}

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

static void	append_node(t_matrix **map, char *point_str)
{
	t_matrix	*new_node;
	t_matrix	*last_node;

	if (!map)
		return ;
	new_node = malloc(sizeof(t_matrix) + 1);
	if (!new_node)
		return ;
	new_node->next = NULL;

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
}

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
}

int	main(int ac, char **av)
{
	int		y_lines;
	int		x_lines;
	char	**first_matrix;
	char	*map_array;
	char	**map_points;
	int		n_points;
	int		i;
	
	if (ac < 2)
		return (1);
	y_lines = get_y_lines_and_valid_map(0, av[1]);
	if (y_lines == -1)
	{
		ft_printf("The map isn't valid!\n");
		return (0);
	}

	first_matrix = get_first_matrix(y_lines, av[1]);
	x_lines = ft_count_words(first_matrix[0], ' ');
	map_array = get_map_array(first_matrix, y_lines);

	n_points = ft_count_words(map_array, ' ');
	map_points = ft_my_split(map_array, ' ', n_points);
	i = -1;

	////////////////////////////////////////////////////
	while(map_points[++i])
		ft_printf("%s ", map_points[i]);
	ft_printf("n_points: %d | n_points + new lines: %d | x*y: %d\n", n_points, i, y_lines * x_lines);
	ft_printf("map_array:\n%s\n", map_array);
	ft_printf("______________________________________________\nlines: %d\n", y_lines);
	ft_printf("x_lines: %d\n", x_lines);


	ft_free_split_mem(n_points, map_points);
	ft_free_split_mem(y_lines, first_matrix);	
	free (map_array);
	return (0);
}
