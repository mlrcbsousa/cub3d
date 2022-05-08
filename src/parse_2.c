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
	parser->line = NULL;
	parser->parts = NULL;
	parser->has_player = FALSE;
	return (parser);
}

// if failure in parse call this method before exit
void	parser_destroy(t_parser *parser)
{
	if (!parser)
		return ;
	if (parser->line)
		free(parser->line);
	if (parser->parts)
		ft_strsfree(parser->parts);
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
	int	a;

	a = 0;
	while (line[a])
	{
		if (line[a] == MAP_NORTH || line[a] == MAP_SOUTH ||
			line[a] == MAP_EAST || line[a] == MAP_WEST)
		{
			if (!parser->has_player)
				parser->has_player = TRUE;
			else
				parse_exit(parser, "Multiple players are not allowed");
		}
		a++;
	}

	mapline_addback(parser, mapline_create(line));
}

void	set_game_wall(char* line, t_parser *parser)
{
	char	**parts;

	parts = ft_split(line, SPACE);
	parser->parts = parts;
	if (!parts || ft_strslen(parts) != 2)
		parse_exit(parser, "Wall element must have 2 parts");
	else if ((ft_streq(parts[0], ELEMENT_NORTH) && parser->wall_north) ||
		(ft_streq(parts[0], ELEMENT_SOUTH) && parser->wall_south) ||
		(ft_streq(parts[0], ELEMENT_EAST) && parser->wall_east) ||
		(ft_streq(parts[0], ELEMENT_WEST) && parser->wall_west))
		parse_exit(parser, "Multiple same wall elements");
	else if (!ft_isfile_ext(parts[1], ".xpm"))
		parse_exit(parser, "Wall file must be .xpm");
	else if (!ft_isfile(parts[1]))
		parse_exit(parser, "invalid .xpm file");

	if (ft_streq(parts[0], ELEMENT_NORTH))
		parser->wall_north = ft_strdup(parts[1]);
	else if (ft_streq(parts[0], ELEMENT_SOUTH))
		parser->wall_south = ft_strdup(parts[1]);
	else if (ft_streq(parts[0], ELEMENT_EAST))
		parser->wall_east = ft_strdup(parts[1]);
	else if (ft_streq(parts[0], ELEMENT_WEST))
		parser->wall_west = ft_strdup(parts[1]);

	ft_strsfree(parser->parts);
	parser->parts = NULL;
}

void	set_game_color(char* line, t_parser *parser)
{
	char	**parts;
	char	**rgb;
	int		color;

	parts = ft_split(line, SPACE);
	parser->parts = parts;
	if (!parts || ft_strslen(parts) != 2)
		parse_exit(parser, "Color element must have 2 parts");
	if ((ft_streq(parts[0], ELEMENT_FLOOR) && parser->color_floor != -1) ||
		(ft_streq(parts[0], ELEMENT_CEILING) && parser->color_ceiling != -1))
		parse_exit(parser, "Multiple same color elements");

	rgb = ft_split(parts[1], COMMA);
	if (!rgb || !is_valid_rgb(rgb))
	{
		ft_strsfree(rgb);
		parse_exit(parser, "Invalid RGB code");
	}

	color = create_trgb(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	if (ft_streq(parts[0], ELEMENT_FLOOR))
		parser->color_floor = color;
	else if (ft_streq(parts[0], ELEMENT_CEILING))
		parser->color_ceiling = color;

	ft_strsfree(rgb);
	ft_strsfree(parser->parts);
	parser->parts = NULL;
}
