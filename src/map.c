/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 01:01:08 by msousa            #+#    #+#             */
/*   Updated: 2022/05/08 03:46:55 by msousa           ###   ########.fr       */
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

int	get_map_width(t_line *mapline)
{
	int	width;

	width = 0;
	while (mapline)
	{
		if (mapline->n_elements > width)
			width = mapline->n_elements;
		mapline = mapline->next;
	}
	return (width);
}

char	**map_init(int map_x, int map_y)
{
	char	**map;
	int		i;

	map = (char **)malloc(sizeof(char *) * map_x + 1);
	if (!map)
		return (NULL);
	*(map + map_x) = NULL;
	i = 0;
	while (i < map_x)
	{
		map[i] = (char *)malloc(sizeof(char) * map_y + 1);
		if (!map[i])
			return (NULL);
		map[i][map_y] = '\0';
		i++;
	}
	return (map);
}

void	map_from_maplines(char **map, t_line *maplines, int map_x, int map_y)
{
	int			i;
	int			j;
	t_element	*e;

	i = 0;
	j = 0;
	while (j < map_y)
	{
		e = maplines->head;
		i = 0;
		while (i < map_x)
		{
			if (e)
			{
				map[i][j] = e->type;
				e = e->next;
			}
			else
				map[i][j] = MAP_SPACE;
			i++;
		}
		maplines = maplines->next;
		j++;
	}
}

void	map_create(t_line *maplines, t_settings *settings)
{
	int		map_x;
	int		map_y;
	char	**map;

	map_x = get_map_width(maplines);
	map_y = maplines_size(maplines);

	// map[x][y];
	map = map_init(map_x, map_y);
	if (!map)
		return ;

	map_from_maplines(map, maplines, map_x, map_y);

	// TODO: test remove
	print_map(map, map_x, map_y);

	settings->map = map;
	settings->width = map_x;
	settings->height = map_y;
}

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
			if (i >= 0 && j >= 0)
			{
				if (i == x && j == y)
				{

				}
				else if (map[i][j])
				{
					valid = (map[i][j] != MAP_SPACE);
					if (!valid)
						return (FALSE);
				}
				else
					return (FALSE);
			}
			else
				return (FALSE);
			if (!valid)
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
