/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:21:19 by isilva-t          #+#    #+#             */
/*   Updated: 2024/07/17 17:19:43 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include "./libs/libft/libft.h"
# include "./libs/ft_printf/ft_printf.h"
# include "./libs/gnl/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# include <stdio.h> //remove before submission

typedef struct s_iterator
{
	int	x;
	int	y;
	int	x_zc;
}			t_iterator;

typedef struct s_pt
{
	long	z;
	int		color;
}			t_pt;

typedef struct s_map
{
	t_pt	**pt;
	int		height;
	int		*width;
	int		y_lines;
	int		fd1;
	char	**lines;
	char	*big_str;
	char	**points;
	char	**info_point;
	int		have_error;
}			t_map;

//a_parsing
int		have_color(const char *str);
void	make_big_array(char *av, t_map *map, char *line);
void	print_created_map(t_map *map, int i);
//long	get_z(const char *str);
//int	get_color(const char	*color_str);

#endif
