/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 14:24:04 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 23:07:04 by josantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	check_all_sides(char **map, int x, int y)
{
	int		i;
	int		j;

	j = y - 1;
	while (j <= y + 1)
	{
		i = x - 1;
		while (i <= x + 1)
		{
			if (i == x && j == y)
			{
				i++;
				continue ;
			}
			if (!(i >= 0 && j >= 0) || !map[i] || !map[i][j]
				|| map[i][j] == MAP_SPACE)
				return (FALSE);
			i++;
		}
		j++;
	}
	return (TRUE);
}

t_bool	is_map_closed(t_settings *s)
{
	int		i;
	int		j;
	t_bool	valid;

	if (!s->map)
		return (FALSE);
	valid = FALSE;
	j = 0;
	while (j < s->height)
	{
		i = 0;
		while (i < s->width)
		{
			if (s->map[i][j] != MAP_WALL
				&& s->map[i][j] != MAP_SPACE)
			{
				valid = check_all_sides(s->map, i, j);
				if (!valid)
					return (FALSE);
			}
			i++;
		}
		j++;
	}
	return (TRUE);
}

void	map_loop(t_app *self, t_bool (*f)(t_app *, int, int))
{
	int			i;
	int			j;
	t_settings	*s;

	s = self->settings;
	if (!s->map)
		return ;
	j = 0;
	while (j < s->height)
	{
		i = 0;
		while (i < s->width)
		{
			if (f(self, i, j))
				return ;
			i++;
		}
		j++;
	}
}
