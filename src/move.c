/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 00:13:00 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 23:15:35 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//  _____     _
// |\ arc     |
// |  \       y
// |    \     |
//            -
// |--x--|
//
//  sin(arc)=y/diagonal
//  cos(arc)=x/diagonal   where diagonal=speed

static void	move_up(t_app *self)
{
	t_point		delta;
	t_player	*player;

	player = self->player;

	delta = point(cos(player->angle), sin(player->angle));
	delta = point_multiply(MOVE, delta);
	delta = point_add(player->p, delta);

	if (is_element_bounded_and_not_wall(self->settings, delta))
		player->p = delta;
}

static void	move_down(t_app *self)
{
	t_point		delta;
	t_player	*player;

	player = self->player;

	delta = point(cos(player->angle), sin(player->angle));
	delta = point_multiply(-MOVE, delta); // or point_subtract with +MOVE
	delta = point_add(player->p, delta);

	if (is_element_bounded_and_not_wall(self->settings, delta))
		player->p = delta;
}

static void	move_left(t_app *self)
{
	t_point		delta;
	t_player	*player;
	int			angle;

	player = self->player;
	angle = trim(player->angle + PI / 2);

	delta = point(cos(angle), sin(angle));
	delta = point_multiply(MOVE, delta);
	delta = point_add(player->p, delta);

	if (is_element_bounded_and_not_wall(self->settings, delta))
		player->p = delta;
}

static void	move_right(t_app *self)
{
	t_point		delta;
	t_player	*player;
	int			angle;

	player = self->player;
	angle = trim(player->angle - PI / 2);

	delta = point(cos(angle), sin(angle));
	delta = point_multiply(MOVE, delta);
	delta = point_add(player->p, delta);

	if (is_element_bounded_and_not_wall(self->settings, delta))
		player->p = delta;
}

void	move(int key, t_app *self)
{
	if (key == KEY_W)
		move_up(self);
	else if (key == KEY_S)
		move_down(self);
	else if (key == KEY_A)
		move_left(self);
	else if (key == KEY_D)
		move_right(self);
	draw(self);
}
