/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:06:33 by msousa            #+#    #+#             */
/*   Updated: 2022/05/08 18:21:21 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	set_player(t_app *self, int i, int j)
{
	char	**map;

	map = self->settings->map;
	if (ft_strchr(ELEMENTS_PLAYER, map[i][j]))
	{
		self->player->x = i;
		self->player->y = j;
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
	// player->dx = ;
	// player->dy = ;
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
