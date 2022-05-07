/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:01:19 by msousa            #+#    #+#             */
/*   Updated: 2022/05/07 18:56:06 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	could_be_game_color(char *line)
{
	char	**parts;
	t_bool	result;

	result = FALSE;
	parts = ft_split(line, ' ');
	if (ft_strslen(parts) == 2)
		result = TRUE;
	if (result)
		result = ft_streq(parts[0], ELEMENT_FLOOR)
			|| ft_streq(parts[0], ELEMENT_CEILING);
	ft_strsfree(parts);
	return (result);
}

t_bool	could_be_game_wall(char *line)
{
	char	**parts;
	t_bool	result;

	result = FALSE;
	parts = ft_split(line, ' ');
	if (ft_strslen(parts) == 2)
		result = TRUE;
	if (result)
		result = ft_streq(parts[0], ELEMENT_NORTH)
			|| ft_streq(parts[0], ELEMENT_SOUTH)
			|| ft_streq(parts[0], ELEMENT_EAST)
			|| ft_streq(parts[0], ELEMENT_WEST);
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

// t_bool	legacy_is_valid_game_mapline(char *line)
// {
// 	// * - invalid characters !{ ' ', '\t', '0', '1', 'N', 'S', 'E', 'W' }
// 	int	len;
// 	int	i;
// 	int	a;
// 	char	**parts;

// 	parts = ft_split(line, ' ');
// 	i = 0;
// 	a = 0;
// 	while (parts[i])
// 	{
// 		len = ft_strlen(parts[i]);
// 		if (parts[i][0] != '1' && parts[i][len - 1] != '1')
// 		{
// 			print_error(NULL, "Invalid map\n");
// 			ft_strsfree(parts);
// 			return (FALSE);
// 		}
// 		while (parts[i][a])
// 		{
// 			if (parts[i][a] == 'N' || parts[i][a] == 'S' ||
// 				parts[i][a] == 'E' || parts[i][a] == 'W')
// 			{
// 				if (player_ready == FALSE)
// 					player_ready = TRUE;
// 				else
// 				{
// 					print_error(NULL, "Multiple players are not allowed\n");
// 					ft_strsfree(parts);
// 					return (FALSE);
// 				}
// 			}
// 			if (!ft_strchr(ELEMENTS_MAP, parts[i][a]))
// 			{
// 				print_error(NULL, "Invalid element inside map\n");
// 				ft_strsfree(parts);
// 				return (FALSE);
// 			}
// 		}
// 	}
// 	return (TRUE);
// }

// size_t	player_count()

t_bool	is_valid_game_map(char **map)
{
	// These have to be done after having full map
	// * - Multiple players or no player.
	// * - Map not closed, check if each map character has no space character
	// 	   around it
	(void)map;
	return (TRUE);
}

