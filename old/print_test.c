/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_section.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:01:26 by isilva-t          #+#    #+#             */
/*   Updated: 2024/07/06 11:00:00 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
static	t_matrix	*print_line(t_matrix *node)
{
	ft_printf("\033[0;31m %d\033[0;32m%d\033[0m%d\033[0;33m%d\033[0m", 
		   node->x, node->y, node->z, node->color);
	node = node->next;
	return (node);
}

static	void	print_nodes(t_matrix *cur_a, int print)
{
	auto int i = 0;
	if (!cur_a || print == 0)
		return ;
	while (cur_a)
	{
		if (cur_a && cur_a->x == 0)
		{
			ft_printf("\n");
			i++;
		}
		if (cur_a)
			cur_a = print_line(cur_a);
	}
	ft_printf("\n");
}

void	print_list(t_matrix **a)
{
	auto t_matrix * cur_prev_a = NULL;
	auto t_matrix * cur_a = NULL;;
	if (a && *a)
	{
		cur_a = *a;
		cur_prev_a = *a;
		cur_prev_a = ft_matrixlast(cur_prev_a);
		while (cur_prev_a->prev)
			cur_prev_a = cur_prev_a->prev;
	}
	print_nodes(cur_a, 0);
	print_nodes(cur_prev_a, 0);
}*/
