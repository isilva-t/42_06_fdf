/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:53:20 by isilva-t          #+#    #+#             */
/*   Updated: 2024/07/06 09:45:46 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	have_syntax_error(char	*str)
{
	if (!str)
		return (1);
	if (!(*str == '-' || *str == '+' || ft_isdigit(*str)))
		return (1);
	if ((*str == '+' || *str == '-') && !(ft_isdigit(*(str + 1))))
		return (1);
	str++;
	while (*str)
	{
		if (!(ft_isdigit(*str)))
			return (1);
		str++;
	}
	return (0);
}

static void	append_node(t_list **stack, int n,
						t_list *new_node, t_list *last_node)
{
	if (!stack)
		return ;
	new_node = malloc(sizeof(t_list) + 1);
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->nbr = n;
	new_node->nbr_to_index = (long)n;
	new_node->index = -1;
	new_node->above_median = -1;
	if (!(*stack))
	{
		new_node->prev = NULL;
		*stack = new_node;
	}
	else
	{
		last_node = ft_lstlast(*stack);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
}
/*
static int	have_duplicated(t_list *stack, int n)
{
	while (stack)
	{
		if (stack->nbr == n)
			return (1);
		stack = stack->next;
	}
	return (0);
}*/

int	init_stack_a(t_matrix **map, char **array, int i, long n)
{
	while (array[i])
	{
		if (have_syntax_error(array[i]))
		{
			ft_printf("Error\n");
			free_stack(a);
			return (1);
		}
		n = atol(array[i]);
		if (n > INT_MAX || n < INT_MIN)
		{
			ft_printf("Error\n");
			free_stack(a);
			return (1);
		}
		/*if (have_duplicated(*a, n))
		{
			ft_printf("Error\n");
			free_stack(a);
			return (1);
		}*/
		append_node(a, (int)n, NULL, NULL);
		i++;
	}
	return (0);
}
