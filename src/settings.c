/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 00:57:45 by msousa            #+#    #+#             */
/*   Updated: 2022/05/11 22:41:23 by msousa           ###   ########.fr       */
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
	settings->paths[WALL_NORTH] = NULL;
	settings->paths[WALL_SOUTH] = NULL;
	settings->paths[WALL_EAST] = NULL;
	settings->paths[WALL_WEST] = NULL;
	settings->map = NULL;
	settings->width = -1;
	settings->height = -1;
	return (settings);
}

void	settings_destroy(t_app *self)
{
	t_settings	*settings;

	settings = self->settings;
	if (!settings)
		return ;
	if (settings->paths[WALL_NORTH])
		free(settings->paths[WALL_NORTH]);
	if (settings->paths[WALL_SOUTH])
		free(settings->paths[WALL_SOUTH]);
	if (settings->paths[WALL_EAST])
		free(settings->paths[WALL_EAST]);
	if (settings->paths[WALL_WEST])
		free(settings->paths[WALL_WEST]);
	if (settings->walls[WALL_NORTH])
		mlx_destroy_image(self->mlx, settings->walls[WALL_NORTH]->img);
	if (settings->walls[WALL_SOUTH])
		mlx_destroy_image(self->mlx, settings->walls[WALL_SOUTH]->img);
	if (settings->walls[WALL_EAST])
		mlx_destroy_image(self->mlx, settings->walls[WALL_EAST]->img);
	if (settings->walls[WALL_WEST])
		mlx_destroy_image(self->mlx, settings->walls[WALL_WEST]->img);
	if (settings->map)
		map_destroy(settings);
	free(settings);
	self->settings = NULL;
}

void	settings_from_parser(t_settings *settings, t_parser *parser)
{
	settings->color_floor = parser->color_floor;
	settings->color_ceiling = parser->color_ceiling;
	settings->paths[WALL_NORTH] = parser->wall_north;
	settings->paths[WALL_SOUTH] = parser->wall_south;
	settings->paths[WALL_EAST] = parser->wall_east;
	settings->paths[WALL_WEST] = parser->wall_west;
	parser->wall_north = NULL;
	parser->wall_south = NULL;
	parser->wall_east = NULL;
	parser->wall_west = NULL;
}

void	settings_init(t_app *self)
{
	t_settings	*settings;
	t_parser	*parser;

	parser = self->parser;
	settings = settings_create();
	if (!settings)
		parse_exit(parser, strerror(errno));
	self->settings = settings;
	map_create(parser->maplines, settings);
	if (!settings->map)
	{
		settings_destroy(self);
		parse_exit(parser, strerror(errno));
	}
	if (!is_map_closed(settings))
	{
		settings_destroy(self);
		parse_exit(parser, "Map not closed");
	}
	settings_from_parser(settings, parser);
	parser_destroy(parser); // the one
}
