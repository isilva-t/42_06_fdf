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
	int		x_cord;
	int		y_cord;
	int		height;
	char	*next;
}			t_matrix;

int	store_map_to_list(t_list **map, char *line_map, int y_ref)
{
	char	**split_array;
	int		n_points;
	int		i;

	i = -1;
	if (!map)
		return (1) ;
	n_points = ft_count_words(line_map, ' ');
	split_array = ft_my_split(line_map, ' ', n_points);
	while (split_array[++i])
		append_node(map, split_array[i]); //verify stack_init in utils
	ft_free_split_mem(n_points, split_array);
	return (0);
}
// continue to parsing and split to nodes all coorinates
// print all cordinates after create a linked list

int	main(int ac, char **av)
{
	char	*line_map;
	int	fd1;
	int	n_words;
	int	y_ref;
	int	have_error;
	t_matrix	**map;
	t_matrix	*tmp;

	y_ref = 0;
	map = NULL;
	fd1 = open(av[1], O_RDONLY);
	if (ac < 2)
	{
		close(fd1);
		return (1);
	}
	line_map = "";
	while (line_map)
	{
		y_ref++;
		line_map = get_next_line(fd1);
		if (!line_map)
		{
			free (line_map);
			break;
		}
		have_error = store_map_to_list(&map, line_map, y_ref);
		if (!*map)
		{
			free (map);
			break;
		}
		if (y_ref == 1)
			tmp = *map;
		ft_printf("%s", map);
		free (map);
	}
	close(fd1);
	return (0);
}
