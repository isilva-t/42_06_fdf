/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:21:19 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/20 16:58:35 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include ".././minilibx-linux/mlx.h"
# include ".././minilibx-linux/mlx_int.h"
# include <X11/keysym.h>
# include ".././libs/libft/libft.h"
# include ".././libs/ft_printf/ft_printf.h"
# include ".././libs/gnl/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>

# define TRUE 1
# define FALSE 0
# define INVALID -1

# define WIDTH	1200
# define HEIGHT	900
# define X_BORDER	60
# define Y_BORDER	40

# define T_DEF "\033[0m"
# define T_BROWN "\033[0;33m"
# define T_CYAN "\033[0;36m"

# ifndef PRINT_COORDS
#  define PRINT_COORDS 0
# endif

# ifndef PRINT_DIMENSIONS
#  define PRINT_DIMENSIONS 0
# endif

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
// vars for draw_line algorithm
	int		delta_x;
	int		delta_y;
	int		x_direction;
	int		y_direction;
	int		err;
	int		e2;
// colors for draw_line
	int		actual_red;
	int		actual_green;
	int		actual_blue;
	int		next_red;
	int		next_green;
	int		next_blue;
	int		delta_color;
	int		delta_z;
	int		color;
// color limits for set color based on z
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
// points to use on draw_line
	t_pt	actual;
	t_pt	next;
}			t_ln_pt;

typedef struct s_map
{
	t_pt	**pt;
	int		offset_p2p;
	float	z_factor;
	int		height;
	int		*width;
	int		max_width;
	int		diagonal;
// vars used for limits	
	t_pt	min_x;
	t_pt	max_x;
	t_pt	min_y;
	t_pt	max_y;
	t_pt	min_z;
	t_pt	max_z;
// vars used for parsing
	int		first_malloc;
	int		fd_lines;
	int		fd1;
	int		get_map_ok;
	char	**lines;
	char	*big_str;
	char	**points;
	char	**info_point;
	int		have_error;
}			t_map;

typedef struct s_imgs
{
	void	*img_p;
	char	*img_px_p;
	int		bits_per_px;
	int		endian;
	int		line_len;
}			t_imgs;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_imgs	img;
	t_map	*map;
}			t_mlx;
//////////////////////////////////////////////////////////////////////////////
// 11_get_map
void		get_map(t_map *map, char *av, t_mlx *d);
//static void	get_z(const char *str, t_map *map, int *y, int *x);
//static void	get_color(const char *color_str, t_map *map,int *y, int *x);
//static void	populate_point(t_map *map, t_iterator *i);
//static void	populate_map(t_map *map);

// 12_get_map_utils
int			have_color(const char *str);
void		make_big_str(char *av, t_map *map, char *line, char *tmp_to_free);
//static void	free_in_make_big_str(char *line, t_map *map);
void		init_map_vars(t_map *map);

//////////////////////////////////////////////////////////////////////////////
// 21_get_map_ready_to_show
void		get_map_ready_to_show(t_map *map);
//static void	set_offset_p2p(t_map *map);
//static void	apply_offset_p2p(t_map *map);
//static void	apply_isometric(t_map *map);
//static void	center_map(t_map *map);

// 22_set_limits
void		get_max_width(t_map *map);
void		set_min_and_max_xyz(t_map *map);
void		set_z_factor(t_map *map);
//static void	init_min_and_max_cords(t_map *map);
//static void	get_diagonal(t_map *map);

//////////////////////////////////////////////////////////////////////////////
// 31_do_mlx_stuff
void		do_mlx_stuff_and_show_map(t_mlx *d, t_map *map);
//static int		free_mlx(t_mlx *d);
//static int		clean_exit(t_mlx *d);
//static void		map_to_mlx_array(t_mlx *d);
//static int		handle_input(int key, t_mlx *d);

// 32_set_color_based_on_z
void		set_color_based_on_z(t_map *map);
//static void	set_min_and_max_z_color(t_ln_pt *data);
//static void	set_color_on_points(t_map *map, t_ln_pt *data);
//static void	set_color_limits(t_ln_pt *data);

// 33_draw_line
void		draw_line(t_mlx *d, t_iterator i, int x_sum, int y_sum);
//static void	my_px_put(t_imgs *img, t_pt pt, int color);
//static void	set_delta_color(t_ln_pt *data);
//static void	set_color_on_point(t_ln_pt *data);
//static void	set_data_to_draw_line(t_ln_pt *data);

// 34_is_pt_inside_window
int			is_pt_inside_window(t_pt pt);

//////////////////////////////////////////////////////////////////////////////
// 88_utils
t_iterator	set_i(int n);
int			get_rgb_color(t_ln_pt *data);
int			only_have_white(t_map *map);
int			is_fdf_file(char *av);
void		print_created_map(t_map *map, int c, int d);

// 99_free_stuff
void		free_stuff(t_map *map);

#endif
