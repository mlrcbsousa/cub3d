/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:10:41 by msousa            #+#    #+#             */
/*   Updated: 2022/05/12 01:52:56 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	has_colors_and_walls(t_parser *parser)
{
	return (parser->wall_north
		&& parser->wall_south
		&& parser->wall_east
		&& parser->wall_west
		&& parser->color_floor != -1
		&& parser->color_ceiling != -1);
}

void	parse_exit(t_parser *parser, char *error)
{
	if (error)
		print_error(NULL, error);
	if (parser)
		parser_destroy(parser);
	exit(EXIT_FAILURE);
}

void	set_elements(char *line, t_parser *parser)
{
	parser->line = line;
	if (could_be_game_color(line))
		set_game_color(line, parser);
	else if (could_be_game_wall(line))
		set_game_wall(line, parser);
	else if (has_colors_and_walls(parser)
		&& could_be_game_mapline(line))
		set_game_mapline(line, parser);
	else
		parse_exit(parser, "invalid game element");
	free(parser->line);
	parser->line = NULL;
}

static int	parse_elements(int fd, t_app *self)
{
	int			status;
	char		*line;
	t_parser	*parser;

	status = 1;
	line = NULL;
	parser = self->parser;
	while (status > 0)
	{
		status = get_next_line(fd, &line);
		if (line && !is_empty_line(line))
			set_elements(line, parser);
	}
	if (status < 0)
		return (EXIT_FAILURE);
	return (status);
}

void	parse(t_app *self, char *cubfile)
{
	int			status;
	t_parser	*parser;

	parser = parser_create();
	if (!parser)
	{
		print_errno(NULL);
		exit(EXIT_FAILURE);
	}
	self->parser = parser;
	status = file_open(cubfile, self, parse_elements);
	if (status || !parser->maplines || !has_colors_and_walls(parser))
		parse_exit(parser, "Invalid cubfile");
	else if (!parser->has_player)
		parse_exit(parser, "map missing one player");
}
