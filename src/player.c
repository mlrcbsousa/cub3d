/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:06:33 by msousa            #+#    #+#             */
/*   Updated: 2022/05/08 19:12:55 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_initial_angle(char direction)
{
	if (direction == MAP_NORTH)
		return (PI / 2);
	else if (direction == MAP_SOUTH)
		return (3 * PI / 2);
	else if (direction == MAP_EAST)
		return (0);
	else if (direction == MAP_WEST)
		return (PI);
	return (-1);
}

t_bool	set_player(t_app *self, int i, int j)
{
	char		**map;
	t_player	*p;

	map = self->settings->map;
	p = self->player;
	if (ft_strchr(ELEMENTS_PLAYER, map[i][j]))
	{
		p->x = i; // TODO: turn into units (relative to pixels)
		p->y = j;

		// set angle based on player (map[i][j])
		p->a = get_initial_angle(map[i][j]);

		// set pdy, pdx
		p->dx = cos(p->a) * 5;
		p->dy = sin(p->a) * 5;

		// change in map
		map[i][j] = MAP_FLOOR;
		return (TRUE);
	}
	return (FALSE);
}

t_player	*player_create(void)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->a = -1;
	player->y = -1;
	player->x = -1;
	player->dx = -1;
	player->dy = -1;
	return (player);
}

// destroy settings, return and exit
void	settings_exit(t_settings *settings, char *error)
{
	if (error)
		print_error(NULL, error);
	if (settings)
		settings_destroy(settings);
	exit(EXIT_FAILURE);
}

void	player_init(t_app *self)
{
	t_player	*player;
	t_settings	*settings;

	settings = self->settings;
	player = player_create();
	if (!player)
		settings_exit(settings, strerror(errno)); // bad alloc

	self->player = player;
	map_loop(self, set_player);

	// TODO: remove
	print_player(player);
	print_map(settings);
}
