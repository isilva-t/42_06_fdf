/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip_fts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:48:14 by isilva-t          #+#    #+#             */
/*   Updated: 2024/07/16 16:48:19 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	make_loweralpha_array(char	*str)
{
	while (str)
	{
		*str = ft_tolower(*str);
		str++;
	}
}

daviduartecf
