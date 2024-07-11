/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:20:58 by isilva-t          #+#    #+#             */
/*   Updated: 2024/07/11 12:52:27 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	char	*str;
	int	fd1;

	fd1 = open(av[1], O_RDONLY);

	str = "";
	(void)ac;
	while (str)
	{
		str = get_next_line(fd1);
		if (!str)
			break; 
		ft_printf("%s", str);
		free (str);
	}
	close(fd1);
	return (0);
}
