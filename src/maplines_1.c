/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maplines_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 16:41:22 by msousa            #+#    #+#             */
/*   Updated: 2022/05/08 16:41:32 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	elements_clear(t_element **elements)
{
	t_element	*tmp;

	while (*elements)
	{
		tmp = *elements;
		*elements = (*elements)->next;
		if (tmp)
			free(tmp);
	}
}

static void	maplines_delone(t_line *mapline)
{
	if (mapline)
	{
		elements_clear(&mapline->head);
		free(mapline);
	}
}

void	maplines_destroy(t_line **maplines)
{
	t_line	*tmp;

	while (*maplines)
	{
		tmp = *maplines;
		*maplines = (*maplines)->next;
		maplines_delone(tmp);
	}
}
