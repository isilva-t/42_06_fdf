/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:09:32 by isilva-t          #+#    #+#             */
/*   Updated: 2024/07/16 17:09:54 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.c"

int	have_color(const char *str)
{
	int	i;

	i = 2;
	if (!str)
		return (0);
	if (ft_strlen(str) < 8 || ft_strlen(str) > 9 
		|| (ft_strlen(str) == 9 && str[8] != '\n'))
		return (-1);
	if (!(*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')))
		return (-1);
	while (str[i] && i < 8)
	{
		if (!(ft_isdigit(str[i]) 
			|| (str[i] >= 'a' && str[i] <= 'f')
			|| (str[i] >= 'A' && str[i] <= 'F')))
			return (-1);
		i++;
	}
	return (1);
}

long	get_z(const char *str)
{
	long	nbr;
	int		i;

	i = 0;
	nbr = (long)INT_MAX + 3;
	if (!str)
		return (nbr);
	if (!(*str == '-' || *str == '+' || ft_isdigit(*str)))
		return (nbr);
	if ((*str == '+' || *str == '-') && !(ft_isdigit(*(str + 1))))
		return (nbr);
	while (str[++i])
	{
		if (str[i] == '\n')
			break;
		if (!(ft_isdigit(str[i])))
			return (nbr);
	}
	nbr = ft_atol(str);
	return (nbr);
}

int	get_color(const char	*color_str)
{
	int	color;
	
	if (have_color(color_str) == 1)
		color = ft_atoi_base(color_str + 2, 16);
	else if (have_color(color_str) == -1)
		color = 0xf000000;
	else
		color = 0xffffff;
	return (color);
}
