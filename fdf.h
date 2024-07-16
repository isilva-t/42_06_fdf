/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:21:19 by isilva-t          #+#    #+#             */
/*   Updated: 2024/07/11 17:56:22 by isilva-t         ###   ########.fr       */
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

typedef struct s_pt
{
	int	z;
	int	color;
}			t_pt;

typedef struct s_map
{
	t_pt	**pts;
	int	height;
	int	*width;
}			t_map;

typedef struct s_split
//parse_1
int	have_color(const char *str);
long	get_z(const char *str);
int	get_color(const char	*color_str);

#endif
