/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 00:13:00 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 23:35:16 by josantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_up(t_app *self)
{
	t_point		p;
	t_player	*player;

	player = self->player;
	p = player->p;
	p = point_move(p, vector(player->angle, MOVE));
	if (is_element_bounded_and_not_wall(self->settings, p))
		player->p = p;
}

static void	move_down(t_app *self)
{
	t_point		p;
	t_player	*player;

	player = self->player;
	p = player->p;
	p = point_move(p, vector(player->angle, -MOVE));
	if (is_element_bounded_and_not_wall(self->settings, p))
		player->p = p;
}

// printf("p: (%f,%f)\n", p.x, p.y);

	// printf("p: (%f,%f)\n", p.x, p.y);
	// printf("s: (%d,%d)\n", s->width, s->height);
	// 	printf("GET HERE\n");

static void	move_left(t_app *self)
{
	t_point		p;
	t_player	*player;

	player = self->player;
	p = player->p;
	p = point_move(p, vector(player->angle + PI / 2, MOVE));
	if (is_element_bounded_and_not_wall(self->settings, p))
		player->p = p;
}

static void	move_right(t_app *self)
{
	t_point		p;
	t_player	*player;

	player = self->player;
	p = player->p;
	p = point_move(p, vector(player->angle - PI / 2, MOVE));
	if (is_element_bounded_and_not_wall(self->settings, p))
		player->p = p;
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
