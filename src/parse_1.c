/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:01:19 by msousa            #+#    #+#             */
/*   Updated: 2022/05/03 20:20:04 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* On the cubfile elements
* - Textures are a file that doesnt exist or not a xpm file.
* - There are multiple textures for the same wall (north wall texture).
* - RGBs dont have 3 numbers, are separated by an invalid character (not a comma) or have values below 0 or above 255.
* - There are invalid characters in the cub.
*/

// use to check everyline from gnl before setting it
t_bool	is_valid_game_element(char *line, t_parser *parser)
{
	return (is_valid_game_color(line, parser)
		|| is_valid_game_wall(line, parser)
		|| is_valid_game_mapline(line));
}

t_bool	is_valid_game_color(char *line, t_parser *parser)
{
	// TODO: complete using
	// - ELEMENT_FLOOR, ELEMENT_CEILING
	// - ft_streq() (clean version of strcmp)

	// sudocode
	// split on space
	// validate length is 2
	// check if first is one of consts above
	// check if this const has already been set
	// check if second is rgb string
	//  - split on comma
	//  - check if each ft_isnumber()
	//  - check if each in range 0 to 255
	(void)line;
	(void)parser;
	return (TRUE);
}

t_bool	is_valid_game_wall(char *line, t_parser *parser)
{
	// TODO: complete using
	// - ELEMENT_NORTH, ELEMENT_SOUTH, ELEMENT_EAST, ELEMENT_WEST
	// - ft_streq() (clean version of strcmp)
	// - ft_isfile() and ft_isfile_ext()

	// sudocode
	// split on space
	// validate length is 2
	// check if first is one of consts above
	// check if this const has already been set
	// check if second is xpm file and is file
	(void)line;
	(void)parser;
	return (TRUE);
}

t_bool	is_valid_game_mapline(char *line)
{
	// * - invalid characters !{ ' ', '\t', '0', '1', 'N', 'S', 'E', 'W' }
	while (*line)
		if (!ft_strchr(ELEMENTS_MAP, *line++))
			return (FALSE);
	return (TRUE);
}

t_bool	is_valid_game_map(char **map)
{
	// These have to be done after having full map
	// * - Multiple players or no player.
	// * - Map not closed, check if each map character has no space character
	// 	   around it
	(void)map;
	return (TRUE);
}

