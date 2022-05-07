/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:01:19 by msousa            #+#    #+#             */
/*   Updated: 2022/05/07 16:44:19 by msousa           ###   ########.fr       */
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
// t_bool	is_valid_game_element(char *line)
// {
// 	char			**parts;
// 	t_validation	*parser;

// 	parser = init_validation();
// 	parts = ft_split(line, ' ');
// 	if (ft_streq(parts[0], "NO") || ft_streq(parts[0], "WE") ||
// 		ft_streq(parts[0], "SO") || ft_streq(parts[0], "EA"))
// 		return (is_valid_game_wall(parts, parser));
// 	else if (ft_streq(parts[0], "F") ||
// 		ft_streq(parts[0], "C"))
// 		return (is_validate_game_color(parts, parser));
// 	check_validation(parser);
// 	if (parser->all_valid == TRUE)
// 		return(is_valid_game_mapline(parts));
// 	ft_strsfree(parts);
// 	return (FALSE);
// }


t_bool	is_valid_game_color(char *line, t_parser *parser)
{
	char	**parts;
	char	**rgb;

	parts = ft_split(line, ' ');
	if (ft_strslen(parts) != 2)
	{
		print_error(NULL, "Invalid color element\n");
		ft_strsfree(parts);
		return (FALSE);
	}
	if ((ft_streq(parts[0], ELEMENT_FLOOR) && parser->color_floor) ||
		(ft_streq(parts[0], ELEMENT_CEILING) && parser->color_ceiling))
	{
		print_error(NULL, "Multiple same color elements\n");
		ft_strsfree(parts);
		return (FALSE);
	}
	rgb = ft_split(parts[1], ',');
	if (!is_valid_rgb(rgb))
	{
		print_error(NULL, "Invalid RGB code\n");
		ft_strsfree(rgb);
		ft_strsfree(parts);
		return (FALSE);
	}
	return (TRUE);
}

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
t_bool	is_valid_game_wall(char *line, t_parser *parser)
{
	char	**parts;

	parts = ft_split(line, ' ');
	if (ft_strslen(parts) != 2)
	{
		print_error(NULL, "Invalid wall element\n");
		ft_strsfree(parts);
		return (FALSE);
	}
	if ((ft_streq(parts[0], ELEMENT_NORTH)  && parser->wall_north) ||
		(ft_streq(parts[0], ELEMENT_SOUTH) && parser->wall_south) ||
		(ft_streq(parts[0], ELEMENT_EAST) && parser->wall_east) ||
		(ft_streq(parts[0], ELEMENT_WEST) && parser->wall_west))
	{
		print_error(NULL, "Multiple same wall elements\n");
		ft_strsfree(parts);
		return (FALSE);
	}
	if (!ft_isfile_ext(parts[1], ".xpm") || !ft_isfile(parts[1]))
	{
		print_error(NULL, "Invalid wall file");
		ft_strsfree(parts);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	is_valid_game_mapline(char *line)
{
	while (*line)
		if (!ft_strchr(ELEMENTS_MAP, *line++))
		{
			print_error(NULL, "Invalid element inside map\n");
			return (FALSE);
		}
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

