/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:01:20 by msousa            #+#    #+#             */
/*   Updated: 2022/05/09 23:55:12 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_app(t_app *self)
{
	settings_destroy(self->settings);
	if (self->player)
		free(self->player);
	mlx_destroy_window(self->mlx, self->mlx_window);
	exit(0);
}

static void	rotate(int key, t_app *self)
{
	t_player *p;

	p = self->player;
	if (key == KEY_LEFT)
	{
		p->angle = trim(p->angle - 0.1);
		p->delta = point_multiply(5, point(cos(p->angle), sin(p->angle)));
	}
	if (key == KEY_RIGHT)
	{
		p->angle = trim(p->angle + 0.1);
		p->delta = point_multiply(5, point(cos(p->angle), sin(p->angle)));
	}
	draw(self);
}

static void	move(int key, t_app *self)
{
	t_player	*player;
	t_point		p;

	player = self->player;
	p = player->p;
	if (key == KEY_A)
		;
	if (key == KEY_D)
		;
	if (key == KEY_W)
		player->p = point_add(p, player->delta);
	if (key == KEY_S)
		player->p = point_subtract(p, player->delta);
	draw(self);
}

static int	key_hook(int key, t_app *self)
{
	if (key == KEY_ESC)
		close_app(self);
	else if (key == KEY_A || key == KEY_D || key == KEY_W
		|| key == KEY_S)
		move(key, self);
	else if (key == KEY_RIGHT || key == KEY_LEFT || key == KEY_UP
		|| key == KEY_DOWN)
		rotate(key, self);
	return (0);
}

void	set_hooks(t_app *self)
{
	mlx_hook(self->mlx_window, ON_KEYDOWN, 1, key_hook, self);
	mlx_hook(self->mlx_window, ON_DESTROY, 0, close_app, self);
}
