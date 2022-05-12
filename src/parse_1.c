/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:01:19 by msousa            #+#    #+#             */
/*   Updated: 2022/05/12 02:17:30 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	is_color_element(char *element)
{
	return (ft_streq(element, ELEMENT_FLOOR)
		|| ft_streq(element, ELEMENT_CEILING));
}

t_bool	could_be_game_color(char *line)
{
	char	**parts;
	t_bool	result;

	result = FALSE;
	parts = ft_split(line, ' ');
	result = (ft_strslen(parts) > 1 && is_color_element(parts[0]));
	ft_strsfree(parts);
	return (result);
}

static t_bool	is_wall_element(char *element)
{
	return (ft_streq(element, ELEMENT_NORTH)
		|| ft_streq(element, ELEMENT_SOUTH)
		|| ft_streq(element, ELEMENT_EAST)
		|| ft_streq(element, ELEMENT_WEST));
}

t_bool	could_be_game_wall(char *line)
{
	char	**parts;
	t_bool	result;

	result = FALSE;
	parts = ft_split(line, ' ');
	if (ft_strslen(parts) > 1)
		if (is_wall_element(parts[0]))
			result = TRUE;
	ft_strsfree(parts);
	return (result);
}

t_bool	could_be_game_mapline(char *line)
{
	while (*line)
		if (!ft_strchr(ELEMENTS_MAP, *line++))
			return (FALSE);
	return (TRUE);
}
