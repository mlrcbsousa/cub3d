/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 00:29:41 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 11:31:58 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	elements_size(t_element *elements)
{
	int	size;

	size = 0;
	while (elements)
	{
		elements = elements->next;
		size++;
	}
	return (size);
}

static t_bool	is_element_bounded(t_settings *s, int x, int y)
{
	return (x >= 0 && y >= 0 && x < s->width && y < s->height);
}

t_bool	is_element_bounded_and_wall(t_settings *s, t_point p)
{
	int	x;
	int	y;

	x = (int)(p.x) >> BITS;
	y = (int)(p.y) >> BITS;
	return (is_element_bounded(s, x, y) && s->map[x][y] == MAP_WALL);
}

t_bool	is_element_bounded_and_not_wall(t_settings *s, t_point p)
{
	int	x;
	int	y;

	x = (int)(p.x) >> BITS;
	y = (int)(p.y) >> BITS;
	return (is_element_bounded(s, x, y) && s->map[x][y] != MAP_WALL);
}
