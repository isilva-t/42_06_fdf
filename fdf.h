/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:21:19 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/08 18:07:45 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include "./libs/libft/libft.h"
# include "./libs/ft_printf/ft_printf.h"
# include "./libs/gnl/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>

# include <stdio.h> //remove before submission

# define T_DEF "\033[0m"
# define T_BROWN "\033[0;33m"
# define T_CYAN "\033[0;36m"
# define TRUE 1
# define FALSE 0
# define INVALID -1

# ifndef PRINT
#  define PRINT 0
# endif

# define WIDTH	1024
# define X_MIN	50
# define X_MAX	550
# define HEIGHT	800
# define Y_MIN	50
# define Y_MAX	450

typedef struct s_iterator
{
	int	x;
	int	y;
	int	x_zc;
}			t_iterator;

typedef struct s_pt
{
	int		x;
	int		y;
	long	z;
	int		color;
}			t_pt;

typedef struct s_ln_pt
{
	int		delta_x;
	int		delta_y;
	int		x_direction;
	int		y_direction;
	int		err;
	int		e2;
	int		actual_red;
	int		actual_green;
	int		actual_blue;
	int		next_red;
	int		next_green;
	int		next_blue;
	int		delta_color;
	int		delta_z;
	int		color;
	int		min_red;
	int		min_green;
	int		min_blue;
	int		max_red;
	int		max_green;
	int		max_blue;
	int		step_red;
	int		step_green;
	int		step_blue;
	t_pt	min_z;
	t_pt	max_z;
	t_pt	actual;
	t_pt	next;
}			t_ln_pt;

typedef struct s_map
{
	t_pt	**pt;
	int		offset_p2p;
//	int		y_sc;
//	int		x_sc;
	int		height;
	int		*width;
	int		max_width;
	t_pt	max_x;
	t_pt	max_y;
	t_pt	min_x;
	t_pt	min_y;
	t_pt	max_z;
	t_pt	min_z;
	int		fd_lines;
	int		fd1;
	int		get_map_ok;
	char	**lines;
	char	*big_str;
	char	**points;
	char	**info_point;
	int		have_error;
}			t_map;

typedef struct s_img
{
	void	*img_p;
	char	*img_px_p;
	int		bits_per_px;
	int		endian;
	int		line_len;
}			t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	*map;
	int		x;
	int		y;
	int		sum_x;
	int		sum_y;
}			t_mlx;

// 00_read_and_handle
int			have_color(const char *str);
void		make_big_str(char *av, t_map *map, char *line);
void		print_created_map(t_map *map, int i);
void		init_map_vars(t_map *map);

// 01_get_map
void		get_map(t_map *map, char *av, t_mlx *d);

// 10_set_color_based_on_z
void		set_color_based_on_z(t_map *map);

// 15_draw_line
void		draw_line(t_mlx *d, t_iterator i, int x_sum, int y_sum);

// 50_do_mlx_stuff
void		do_mlx_stuff(t_mlx *d);

// 95_utils
t_iterator	set_i(int n);
int			get_rgb_color(t_ln_pt *data);

// 99_free_stuff
void		free_stuff(t_map *map);

#endif
