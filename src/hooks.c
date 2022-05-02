/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:01:20 by msousa            #+#    #+#             */
/*   Updated: 2022/05/01 18:16:07 by msousa           ###   ########.fr       */
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
	if (key == KEY_RIGHT || key == KEY_LEFT)
		;
	else if (key == KEY_UP || key == KEY_DOWN)
		;
	draw(self);
}

static void	move(int key, t_app *self)
{
	if (key == KEY_A || key == KEY_D)
		;
	else if (key == KEY_W  || key == KEY_S)
		;
	draw(self);
}

static int	key_hook(int key, t_app *self)
{
	// TODO: remove
	printf("Test %d\n", key);
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
