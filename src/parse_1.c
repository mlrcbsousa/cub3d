/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:01:19 by msousa            #+#    #+#             */
/*   Updated: 2022/05/04 17:36:09 by josantos         ###   ########.fr       */
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
t_bool	is_valid_game_element(char *line)
{
	char			**split_line;
	t_validation	*valid;
	
	valid = init_validation();
	split_line = ft_split(line, " ");
	if (ft_strcmp(split_line[0], "NO") || ft_strcmp(split_line[0], "WE") ||
		ft_strcmp(split_line[0], "SO") || ft_strcmp(split_line[0], "EA"))
		return (is_valid_game_wall(split_line, valid));
	else if (ft_strcmp(split_line[0], "F") ||
		ft_strcmp(split_line[0], "C"))
		return (is_validate_game_color(split_line, valid));
	check_validation(valid);
	if (valid->all_valid == TRUE)
		return(is_valid_game_mapline(split_line));
	split_free(split_line);
	return (FALSE);
}

t_bool	is_valid_rgb(char **colors)
{
	int	i;
	int	color;

	i = 0;
	if (ft_arraylen(colors) != 3)
		return (FALSE);
	while (colors[i])
	{
		if (!ft_isnumber(colors[i]))
			return (FALSE);
		color = ft_atoi(colors[i]);
		if (color < 0 || color > 255)
			return (FALSE);
	}
}

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
t_bool	is_valid_game_color(char **split_line, t_validation *valid)
{
	char	**split_rgb;
	
	if (ft_arraylen(split_line) != 2)
	{
		print_error(NULL, "Invalid color element\n");
		split_free(split_line);
		return (FALSE);
	}
	if (ft_strcmp(split_line[0], "F")  && valid->ceiling ||
		ft_strcmp(split_line[0], "C") && valid->floor)
	{
		print_error(NULL, "Multiple same color elements\n");
		split_free(split_line);
		return (FALSE);
	}
	split_rgb = ft_split(split_line[1], ",");
	if (!is_valid_rgb(split_rgb))
	{
		print_error(NULL, "Invalid RGB code\n");
		split_free(split_line);
		split_free(split_rgb);
		return (FALSE);
	}
	validate_element(split_line[0], valid);
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
t_bool	is_valid_game_wall(char **split_line, t_validation *valid)
{
	if (ft_arraylen(split_line) != 2)
	{
		print_error(NULL, "Invalid wall element\n");
		split_free(split_line);
		return (FALSE);
	}
	if (ft_strcmp(split_line[0], "NO")  && valid->north_wall ||
		ft_strcmp(split_line[0], "WE") && valid->west_wall ||
		ft_strcmp(split_line[0], "SO") && valid->south_wall ||
		ft_strcmp(split_line[0], "EA") && valid->east_wall)
	{
		print_error(NULL, "Multiple same wall elements\n");
		split_free(split_line);
		return (FALSE);
	}
	if (!ft_isfile_ext(split_line[1], ".xpm") || !ft_isfile(split_line[1]))
	{
		print_error(NULL, "Invalid wall file");
		split_free(split_line);
		return (FALSE);
	}
	validate_element(split_line[0], valid);
	return (TRUE);
}

t_bool	is_valid_game_mapline(char **split_line)
{
	// * - invalid characters !{ ' ', '\t', '0', '1', 'N', 'S', 'E', 'W' }
	int	len;
	int	i;
	int	a;
	static t_bool	player_ready = FALSE;
	
	i = 0;
	a = 0;
	while (split_line[i])
	{
		len = ft_strlen(split_line[i]);
		if (split_line[i][0] != '1' && split_line[i][len - 1] != '1')
		{
			print_error(NULL, "Invalid map\n");
			split_free(split_line);
			return (FALSE);
		}
		while (split_line[i][a])
		{
			if (split_line[i][a] == 'N' || split_line[i][a] == 'S' ||
				split_line[i][a] == 'E' || split_line[i][a] == 'W')
			{
				if (player_ready == FALSE)
					player_ready = TRUE;
				else
				{
					print_error(NULL, "Multiple players are not allowed\n");
					split_free(split_line);
					return (FALSE);
				}
			}
			if (!ft_strchr(ELEMENTS_MAP, split_line[i][a]))
			{
				print_error(NULL, "Invalid element inside map\n");
				split_free(split_line);
				return (FALSE);
			}
		}
	}
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

