/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 18:38:35 by msousa            #+#    #+#             */
/*   Updated: 2022/05/03 19:45:04 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_parser	*parser_create(void)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->color_floor = -1;
	parser->color_ceiling = -1;
	parser->wall_north = NULL;
	parser->wall_south = NULL;
	parser->wall_east = NULL;
	parser->wall_west = NULL;
	parser->maplines = NULL;
	return (parser);
}

// if failure in parse call this method before exit
void	parser_destroy(t_parser *parser)
{
	if (!parser)
		return ;
	if (parser->wall_north)
		free(parser->wall_north);
	if (parser->wall_south)
		free(parser->wall_south);
	if (parser->wall_east)
		free(parser->wall_east);
	if (parser->wall_west)
		free(parser->wall_west);
	if (parser->maplines)
		maplines_destroy(parser->maplines);
	free(parser);
}


void	set_game_mapline(char* line, t_parser *parser)
{
	(void)line;
	(void)parser;
	// add_back_maplines
}

void	set_game_wall(char* line, t_parser *parser)
{
	char	**parts;

	parts = ft_split(line, SPACE);
	if (!parts)
		parse_exit(line, parser);

	if (ft_streq(parts[0], ELEMENT_NORTH))
		parser->wall_north = parts[1];
	if (ft_streq(parts[0], ELEMENT_SOUTH))
		parser->wall_south = parts[1];
	if (ft_streq(parts[0], ELEMENT_EAST))
		parser->wall_east = parts[1];
	if (ft_streq(parts[0], ELEMENT_WEST))
		parser->wall_west = parts[1];

	free(parts[0]);
	free(line);
}

void	set_game_color(char* line, t_parser *parser)
{
	char	**parts;
	char	**rgb;

	parts = ft_split(line, SPACE);
	if (!parts)
		parse_exit(line, parser);

	rgb = ft_split(parts[1], COMMA);
	if (!rgb)
	{
		ft_splitfree(parts);
		parse_exit(line, parser);
	}

	if (ft_streq(parts[0], ELEMENT_FLOOR))
		parser->color_floor =
			create_trgb(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	if (ft_streq(parts[0], ELEMENT_CEILING))
		parser->color_ceiling =
			create_trgb(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));

	ft_splitfree(rgb);
	ft_splitfree(parts);
	free(line);
}
