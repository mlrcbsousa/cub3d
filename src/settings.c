/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 00:57:45 by msousa            #+#    #+#             */
/*   Updated: 2022/05/08 15:57:50 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_settings	*settings_create(void)
{
	t_settings	*settings;

	settings = (t_settings *)malloc(sizeof(t_settings));
	if (!settings)
		return (NULL);
	settings->color_floor = -1;
	settings->color_ceiling = -1;
	settings->wall_north = NULL;
	settings->wall_south = NULL;
	settings->wall_east = NULL;
	settings->wall_west = NULL;
	settings->player = NULL;
	settings->map = NULL;
	settings->width = -1;
	settings->height = -1;
	return (settings);
}

void	settings_destroy(t_settings *settings)
{
	if (!settings)
		return ;
	if (settings->wall_north)
		free(settings->wall_north); // TODO: proper mlx image destroy
	if (settings->wall_south)
		free(settings->wall_south);
	if (settings->wall_east)
		free(settings->wall_east);
	if (settings->wall_west)
		free(settings->wall_west);
	if (settings->player)
		free(settings->player);
	if (settings->map)
		ft_strsfree(settings->map);
	free(settings);
}

void	settings_from_parser(t_settings *settings, t_parser *parser)
{
	settings->color_floor = parser->color_floor;
	settings->color_ceiling = parser->color_ceiling;

	// TODO: leave for later, use basic colors for now
	// settings->wall_north = image_create(parser->wall_north);
	// settings->wall_south = image_create(parser->wall_south);
	// settings->wall_east = image_create(parser->wall_east);
	// settings->wall_west = image_create(parser->wall_west);

	// TODO:
	// settings->player = NULL;
}

void	settings_init(t_app *self)
{
	t_settings	*settings;
	t_parser	*parser;

	parser = self->parser;
	settings = settings_create();
	if (!settings)
		parse_exit(parser, errno); // bad alloc

	self->settings = settings;
	map_create(parser->maplines, settings);
	if (!settings->map)
	{
		settings_destroy(settings);
		parse_exit(parser, errno); // bad alloc
	}

	if (!is_map_closed(settings))
	{
		settings_destroy(settings);
		parse_exit(parser, "Map not closed");
	}

	settings_from_parser(settings, parser);
	parser_destroy(parser); // the one
}
