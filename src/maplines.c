/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maplines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:20:28 by msousa            #+#    #+#             */
/*   Updated: 2022/05/08 14:23:21 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	maplines_size(t_line *mapline)
{
	int	size;

	size = 0;
	while (mapline)
	{
		mapline = mapline->next;
		size++;
	}
	return (size);
}

void	maplines_destroy(t_line *maplines)
{
	// TODO: linked list of linked lists destroy
	(void)maplines;
}
