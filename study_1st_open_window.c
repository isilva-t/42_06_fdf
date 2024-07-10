/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   study_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:10:06 by isilva-t          #+#    #+#             */
/*   Updated: 2024/07/09 17:45:29 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_linux/mlx.h"
#include <stdlib.h>

#define MALLOC_ERROR	1
#define WIDTH			400
#define HEIGHT			400

int main()
{
	void	*mlx_connection;
	void	*mlx_window;

	mlx_connection = mlx_init(); //conectes to X Server with mlx_init
	if (!mlx_connection)
		return (MALLOC_ERROR);
					//my pointer receives window, that I pass
	//						my pointer to mlx,   dimensiones,     and name
	//							connection ptr			unsigned int	string
	mlx_window = mlx_new_window(mlx_connection, HEIGHT, WIDTH, "My window");
	if (!mlx_window)
	{
		mlx_destroy_display(mlx_connection); //passing my connection as a parameter
		free(mlx_connection); //free my pointer was malloc'd by mlx_init()
		return (MALLOC_ERROR);
	}
	mlx_loop(mlx_connection); //keeps window alive on screen

	mlx_destroy_window(mlx_connection, mlx_window); //1st destroy window
					//passing connection	and window
	mlx_destroy_display(mlx_connection); //destroy DISPLAY, AFTER WINDOW
	free(mlx_connection); //free connection
	return (0);
}
