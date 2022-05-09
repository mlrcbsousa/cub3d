/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 14:24:04 by msousa            #+#    #+#             */
/*   Updated: 2022/05/09 13:20:28 by msousa           ###   ########.fr       */
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
				continue;
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

t_bool	is_map_closed(t_settings *settings)
{
	int		i;
	int		j;
	t_bool	valid;

	if (!settings->map)
		return (FALSE);
	valid = FALSE;
	j = 0;
	while (j < settings->height)
	{
		i = 0;
		while (i < settings->width)
		{
			if (settings->map[i][j] != MAP_WALL
				&& settings->map[i][j] != MAP_SPACE)
			{
				valid = check_all_sides(settings->map, i, j);
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

	if (!self->settings->map)
		return ;
	j = 0;
	while (j < self->settings->height)
	{
		i = 0;
		while (i < self->settings->width)
		{
			if (f(self, i, j))
				return ;
			i++;
		}
		j++;
	}
}
