/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 01:01:08 by msousa            #+#    #+#             */
/*   Updated: 2022/05/08 02:20:24 by msousa           ###   ########.fr       */
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

char	**map_create(t_line *maplines)
{
	int		map_x;
	int		map_y;
	char	**map;

	map_x = get_map_width(maplines);
	map_y = maplines_size(maplines);

	// map[x][y];
	map = map_init(map_x, map_y);
	if (!map)
		return (NULL);

	map_from_maplines(map, maplines, map_x, map_y);

	// TODO: test remove
	print_map(map, map_x, map_y);

	return (map);
}

t_bool	is_map_closed(char **map)
{
	return (!map);
}
