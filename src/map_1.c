/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 14:24:04 by msousa            #+#    #+#             */
/*   Updated: 2022/05/08 15:11:52 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	check_all_sides(char **map, int x, int y)
{
	int		i;
	int		j;
	t_bool	valid;

	j = y - 1;
	valid = FALSE;
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
			// if (!(i >= 0 && j >= 0))
			// 	return (FALSE);
			// else if (!map[i])
			// 	return (FALSE);
			// else if (!map[i][j])
			// 	return (FALSE);
			// else if (map[i][j] == MAP_SPACE)
			// 	return (FALSE);
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
