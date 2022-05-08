/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:01:20 by msousa            #+#    #+#             */
/*   Updated: 2022/05/08 22:27:55 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_app(t_app *self)
{
	mlx_destroy_window(self->mlx, self->mlx_window);
	exit(0);
}

static void	view(int key, t_app *self)
{
	t_player *p;

	p = self->player;
	if (key == KEY_LEFT)
	{
		p->a -= 0.1;
		if (p->a < 0)
			p->a += 2 * PI;
		p->dx = cos(p->a) * 5;
		p->dy = sin(p->a) * 5;
	}
	if (key == KEY_RIGHT)
	{
		p->a += 0.1;
		if (p->a > 2 * PI)
			p->a -= 2 * PI;
		p->dx = cos(p->a) * 5;
		p->dy = sin(p->a) * 5;
	}

	print_player(p);

	draw(self);
}

static void	move(int key, t_app *self)
{
	t_player *p;

	p = self->player;
	// 5 to change for useful constant
	// if (key == KEY_A)
	// 	p->x -= 5;
	// if (key == KEY_D)
	// 	p->x += 5;
	if (key == KEY_W)
	{
		p->x += p->dx;
		p->y += p->dy;
	}
	if (key == KEY_S)
	{
		p->x -= p->dx;
		p->y -= p->dy;
	}

	print_player(p);

	draw(self);
}

static int	key_hook(int key, t_app *self)
{
	// TODO: remove
	printf("\nTest %d", key);
	if (key == KEY_ESC)
		close_app(self);
	else if (key == KEY_A || key == KEY_D || key == KEY_W
		|| key == KEY_S)
		move(key, self);
	else if (key == KEY_RIGHT || key == KEY_LEFT || key == KEY_UP
		|| key == KEY_DOWN)
		view(key, self);
	return (0);
}

void	set_hooks(t_app *self)
{
	mlx_key_hook(self->mlx_window, key_hook, self);
	mlx_hook(self->mlx_window, DESTROY_NOTIFY, 0, close_app, self);
}
