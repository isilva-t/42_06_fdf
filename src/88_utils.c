/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   88_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:24:18 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/20 16:46:17 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_iterator	set_i(int n);
int			get_rgb_color(t_ln_pt *data);
int			only_have_white(t_map *map);
int			is_fdf_file(char *av);
void		print_created_map(t_map *map, int c, int d);

t_iterator	set_i(int n)
{
	t_iterator	i;

	i.x = n;
	i.y = n;
	return (i);
}

int	get_rgb_color(t_ln_pt *data)
{
	int	color;

	color = ((data->actual_red << 16)
			| (data->actual_green << 8)
			| data->actual_blue);
	return (color);
}

int	only_have_white(t_map *map)
{
	t_iterator	i;

	i.y = -1;
	while (++i.y < map->height)
	{
		i.x = -1;
		while (++i.x < map->width[i.y])
		{
			if (map->pt[i.y][i.x].color != 0xffffff)
				return (FALSE);
		}
	}
	return (TRUE);
}

int	is_fdf_file(char *av)
{
	int	len;
	int	return_val;

	return_val = FALSE;
	len = ft_strlen(av);
	if (len <= 4)
		return (return_val);
	if (av[len - 4] == '.'
		&& av[len - 3] == 'f'
		&& av[len - 2] == 'd'
		&& av[len - 1] == 'f')
		return_val = TRUE;
	else
		return_val = FALSE;
	if (return_val == TRUE && len > 4 && av[len - 5] == '/')
		return_val = FALSE;
	return (return_val);
}

void	print_created_map(t_map *map, int c, int d)
{
	t_iterator	i;

	i.y = 0;
	while (i.y < map->fd_lines && c == TRUE)
	{
		ft_printf("\n");
		i.x = 0;
		while (i.x < map->width[i.y])
		{
			ft_printf("%s%d%s%d\033[0m ", T_DEF, \
			map->pt[i.y][i.x].z, T_BROWN, map->pt[i.y][i.x].color);
			i.x++;
		}
		i.y++;
	}
	if (d == TRUE)
	{
		ft_printf("%s\nmap.width[0]: %d\nmap.height: %d%s\n", \
			T_CYAN, map->width[0], map->fd_lines, T_DEF);
		ft_printf("HEIGHT ^: %d, WIDTH >: %d\n", HEIGHT, WIDTH);
	}
}
