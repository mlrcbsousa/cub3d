/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:01:20 by msousa            #+#    #+#             */
/*   Updated: 2022/04/21 11:36:06 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_app(t_app *self)
{
	mlx_destroy_window(self->mlx, self->mlx_window);
	exit(0);
}

static void	move(int key, t_app *self)
{
	if (key == ARROW_RIGHT || key == ARROW_LEFT)
		;
	else if (key == ARROW_UP || key == ARROW_DOWN)
		;
	draw(self);
}

static int	key_hook(int key, t_app *self)
{
	if (key == KEY_ESC)
		close_app(self);
	else if (key == ARROW_UP || key == ARROW_DOWN || key == ARROW_LEFT
		|| key == ARROW_RIGHT)
		move(key, self);
	else if (key == KEY_C)
	{
		draw(self);
	}
	return (0);
}

void	set_hooks(t_app *self)
{
	mlx_key_hook(self->mlx_window, key_hook, self);
	mlx_hook(self->mlx_window, DESTROY_NOTIFY, 0, close_app, self);
}
