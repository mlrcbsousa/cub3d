/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:01:20 by msousa            #+#    #+#             */
/*   Updated: 2022/04/29 16:40:54 by josantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int	close_app(t_app *self)
{
	mlx_destroy_window(self->mlx, self->mlx_window);
	exit(0);
}

static void	view(int key, t_app *self)
{
	if (key == ARROW_RIGHT || key == ARROW_LEFT)
		;
	else if (key == ARROW_UP || key == ARROW_DOWN)
		;
	draw(self);
}

static void	move(int key, t_app *self)
{
	if (key == A_KEY || key == D_KEY)
		;
	else if (key == W_KEY  || key == S_KEY)
		;
	draw(self);
}

static int	key_hook(int key, t_app *self)
{
	printf("%d\n", key);
	if (key == KEY_ESC)
		close_app(self);
	else if (key == A_KEY || key == D_KEY || key == W_KEY
		|| key == S_KEY)
		move(key, self);
	else if (key == ARROW_RIGHT || key == ARROW_LEFT || key == ARROW_UP
		|| key == ARROW_DOWN)
		view(key, self);
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
