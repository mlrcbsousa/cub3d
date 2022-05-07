/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:10:41 by msousa            #+#    #+#             */
/*   Updated: 2022/05/07 22:38:55 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// colors and walls must be set already at this point
static t_bool	has_colors_and_walls(t_parser *parser)
{
	return (parser->wall_north
		&& parser->wall_south
		&& parser->wall_east
		&& parser->wall_west
		&& parser->color_floor != -1
		&& parser->color_ceiling != -1);
}

// destroy parser, return and exit
void	parse_exit(t_parser *parser, char *error)
{
	if (error)
		print_error(NULL, error);
	if (parser)
		parser_destroy(parser);
	exit(EXIT_FAILURE);
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

		// for test TODO: remove
		if (line)
			printf("%s\n", line);

		// TODO: is an empty line NULL?
		if (line && !is_empty_line(line))
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
	}
	// TODO: maybe useless
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
		print_errno(NULL); // bad alloc should be in errno
		exit(EXIT_FAILURE);
	}

	self->parser = parser;
	status = file_open(cubfile, self, parse_elements);

	// TEST TODO: remove
	print_parser(parser);

	// The only way status could fail here is if something fails with gnl
	if (status || !parser->maplines || !has_colors_and_walls(parser))
		parse_exit(parser, "Invalid cubfile");

	// TODO: (this should probably be next chunk of program, separate file)
	// - transform maplines to char** and get some data (width and height)
	// - validate map after transform because map[i][j] is easier for
	// 	 closed-map validation
	// - destroy maplines
}
