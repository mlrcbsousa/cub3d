/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:01:19 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 23:55:53 by josantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	could_be_game_color(char *line)
{
	char	**parts;
	t_bool	result;

	result = FALSE;
	parts = ft_split(line, ' ');
	result = (ft_strslen(parts) > 1 && (ft_streq(parts[0], ELEMENT_FLOOR))
		|| ft_streq(parts[0], ELEMENT_CEILING));
	ft_strsfree(parts);
	return (result);
}

t_bool	could_be_game_wall(char *line)
{
	char	**parts;
	t_bool	result;
	
	result = FALSE;
	parts = ft_split(line, ' ');
	result = ft_strslen(parts) > 1 && (ft_streq(parts[0], ELEMENT_NORTH)
		|| ft_streq(parts[0], ELEMENT_SOUTH)
		|| ft_streq(parts[0], ELEMENT_EAST)
		|| ft_streq(parts[0], ELEMENT_WEST));
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
