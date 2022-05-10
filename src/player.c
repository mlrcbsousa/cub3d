/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:06:33 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 14:48:45 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_initial_angle(char direction)
{
	printf("direction: %c\n", direction);
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
	t_player	*player;

	map = self->settings->map;
	player = self->player;
	if (ft_strchr(ELEMENTS_PLAYER, map[i][j]))
	{
		player->p = point((i << BITS) + SIZE / 2, (j << BITS) + SIZE / 2);
		player->angle = get_initial_angle(map[i][j]);
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
	player->angle = -1;
	player->p = point(-1, -1);
	return (player);
}

void	player_init(t_app *self)
{
	t_player	*player;
	t_settings	*settings;

	settings = self->settings;
	player = player_create();
	if (!player)
		settings_exit(settings, strerror(errno));

	// TODO: remove
	print_map(settings);

	self->player = player;
	map_loop(self, set_player);
}
