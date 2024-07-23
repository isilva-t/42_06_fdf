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

# include "./minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include "./libs/libft/libft.h"
# include "./libs/ft_printf/ft_printf.h"
# include "./libs/gnl/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

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

# define WIDTH	400
# define HEIGHT	400
# define SIDE_LEN	400

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
	int		y_sc;
	int		x_sc;
	int		height;
	int		*width;
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
	void	*img_ptr;
	char	*img_px_ptr;
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

//00_read_and_handle
int		have_color(const char *str);
void	make_big_str(char *av, t_map *map, char *line);
void	print_created_map(t_map *map, int i);
void	init_map_vars(t_map *map);
//01_get_map
void	get_map(t_map *map, char *av, t_mlx *d);

// 99_free_stuff
void	free_stuff(t_map *map);


#endif
