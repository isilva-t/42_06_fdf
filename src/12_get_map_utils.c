/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_get_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:51:10 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/20 16:52:54 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		init_map_vars(t_map *map);
int			have_color(const char *str);
static void	free_in_make_big_str(char *line, t_map *map);
void		make_big_str(char *av, t_map *map, char *line, char *tmp_to_free);

void	init_map_vars(t_map *map)
{
	map->have_error = FALSE;
	map->fd_lines = 0;
	map->height = 0;
	map->width = 0;
	map->max_width = 0;
	map->get_map_ok = FALSE;
	map->first_malloc = 0;
}

int	have_color(const char *str)
{
	int	i;

	i = 2;
	if (!str)
		return (FALSE);
	if (ft_strlen(str) > 9
		|| (ft_strlen(str) == 9 && str[8] != '\n'))
		return (INVALID);
	if (!(*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')))
		return (INVALID);
	while (str[i] && i < 8)
	{
		if (!(ft_isdigit(str[i])
				|| (str[i] >= 'a' && str[i] <= 'f')
				|| (str[i] >= 'A' && str[i] <= 'F')))
			return (INVALID);
		i++;
	}
	if (str[2])
		return (TRUE);
	return (INVALID);
}

static void	free_in_make_big_str(char *line, t_map *map)
{
	free (line);
	if (map->first_malloc == 1)
		free (map->big_str);
}

void	make_big_str(char *av, t_map *map, char *line, char *tmp_to_free)
{
	map->fd1 = open(av, O_RDONLY);
	if (map->fd1 < 0)
	{
		map->have_error = TRUE;
		return ;
	}
	map->big_str = (char *)ft_calloc(1, sizeof(char) + 1);
	if (!map->big_str)
		return ;
	while (line)
	{
		map->first_malloc++;
		line = get_next_line(map->fd1);
		if (!line)
		{
			free_in_make_big_str(line, map);
			break ;
		}
		tmp_to_free = map->big_str;
		map->big_str = ft_strjoin(map->big_str, line);
		free (tmp_to_free);
		free (line);
		map->fd_lines += 1;
	}
	close(map->fd1);
}
