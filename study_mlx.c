/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   study_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:10:06 by isilva-t          #+#    #+#             */
/*   Updated: 2024/07/09 15:22:53 by isilva-t         ###   ########.fr       */
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

	mlx_connection = mlx_init();
	if (!mlx_connection)
		return (MALLOC_ERROR);

	mlx_window = mlx_new_window(mlx_connection,
							 HEIGHT,
							 WIDTH,
							 "My window");
	if (!mlx_window)
	{
		mlx_destroy_display(mlx_connection);
		free(mlx_connection);
		return (MALLOC_ERROR);
	}
	mlx_loop(mlx_connection);

	mlx_destroy_window(mlx_connection, mlx_window); 
	mlx_destroy_display(mlx_connection);
	free(mlx_connection);
}
