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
/*
typedef struct s_map_size
{
	int	x_size;
	int	y_size;
}			t_map_size;

typedef struct s_matrix
{
	int		x;
	int		y;
	int		x;
	char	*prev;
	char	*next;
}			t_matrix;

int	store_map_to_list(t_list **map, char *line_map, int y_ref)
{
	char	**split_line;
	char	**info_to_node;
	int		n_points;
	int		i;

	i = -1;
	if (!map)
		return (1) ;
	n_points = ft_count_words(line_map, ' ');
	split_line = ft_my_split(line_map, ' ', n_points);
	while (split_line[++i])
		append_node(map, split_line[i]); //verify stack_init in utils
	ft_free_split_mem(n_points, split_array);
	return (0);
}*/
// continue to parsing and split to nodes all coorinates
// print all cordinates after create a linked list


int	get_y_lines(int y_lines, char *av)
{
	int	fd1;
	char	*line;

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
	int		i;

	i = -1;
	map_array = "";
	while (++i < y_lines)
		map_array = ft_strjoin(map_array, first_matrix[i]);
	return (map_array);
}

int	main(int ac, char **av)
{
	int		y_lines;
	int		x_lines;
	char	**first_matrix;
	char	*map_array;
	
	if (ac < 2)
		return (1);
	y_lines = get_y_lines(0, av[1]);
	first_matrix = get_first_matrix(y_lines, av[1]);
	x_lines = ft_count_words(first_matrix[0], ' ');
	map_array = get_map_array(first_matrix, y_lines);

	ft_printf("map_array:\n%s\n", map_array);
	ft_printf("______________________________________________\nlines: %d\n", y_lines);
	ft_printf("x_lines: %d\n", x_lines);
	ft_free_split_mem(y_lines, first_matrix);	
	//ft_free_split_mem(x_lines, *second_matrix);
	//free (second_matrix);
	return (0);
}
