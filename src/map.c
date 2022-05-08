/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 01:01:08 by msousa            #+#    #+#             */
/*   Updated: 2022/05/08 15:48:23 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_map_width(t_line *mapline)
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

static char	**map_init(int width, int height)
{
	char	**map;
	int		i;

	map = (char **)malloc(sizeof(char *) * width + 1);
	if (!map)
		return (NULL);
	map[width] = NULL;
	// *(map + width) = NULL;
	i = 0;
	while (i < width)
	{
		map[i] = (char *)malloc(sizeof(char) * height + 1);
		if (!map[i])
			return (NULL);
		map[i][height] = '\0';
		i++;
	}
	return (map);
}

static void	map_from_maplines(char **map, t_line *maplines, int x, int y)
{
	int			i;
	int			j;
	t_element	*e;

	j = 0;
	while (j < y)
	{
		i = 0;
		e = maplines->head;
		while (i < x)
		{
			if (e)
			{
				map[i][j] = e->type;
				e = e->next;
			}
			else
				map[i][j] = (char)MAP_SPACE;
			i++;
		}
		maplines = maplines->next;
		j++;
	}
}

void	map_create(t_line *maplines, t_settings *settings)
{
	int		width;
	int		height;
	char	**map;

	width = get_map_width(maplines);
	height = maplines_size(maplines);

	map = map_init(width, height);
	if (!map)
		return ;

	map_from_maplines(map, maplines, width, height);

	// TODO: remove
	print_map(map, width, height);

	settings->map = map;
	settings->width = width;
	settings->height = height;
}
