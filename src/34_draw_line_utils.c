/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   34_draw_line_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:33:11 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/26 10:33:15 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_pt_inside_window(t_pt pt)
{
	if (pt.y < HEIGHT && pt.y >= 0
		&& pt.x >= 0 && pt.x < WIDTH)
		return (TRUE);
	return (FALSE);
}
