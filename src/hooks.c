/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:01:20 by msousa            #+#    #+#             */
/*   Updated: 2022/05/11 18:07:19 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_app(t_app *self)
{
	settings_destroy(self->settings);
	if (self->player)
		free(self->player);
	mlx_destroy_window(self->mlx, self->mlx_window);
	exit(0);
}

static void	rotate(int key, t_app *self)
{
	t_player	*p;

	p = self->player;
	if (key == KEY_LEFT)
		p->angle = trim(p->angle - 0.1);
	if (key == KEY_RIGHT)
		p->angle = trim(p->angle + 0.1);
	draw(self);
}

int	key_hook(int key, t_app *self)
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
