/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 00:13:00 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 00:24:10 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_up(t_app *self)
{
	t_player	*player;
	t_point		p;

	player = self->player;
	p = player->p;
	player->p = point_add(p, player->delta);

// 	p.x = conf->pov->p.x;
// 	p.y = conf->pov->p.y;
// 	p = add_vec(p, vec(conf->pov->angle, conf->pov->mag));
// 	if (p.x > conf->pov->width || p.x < 0 || p.y > conf->pov->height || p.y < 0)
// 		return ;
// 	if (conf->map[(int)(p.y / TILE_SIZE)][(int)(p.x / TILE_SIZE)] != '1')
// 	{
// 		conf->pov->p.y = round(p.y);
// 		conf->pov->p.x = round(p.x);
// 	}
}

static void	move_down(t_app *self)
{
	t_player	*player;
	t_point		p;

	player = self->player;
	p = player->p;
	player->p = point_subtract(p, player->delta);

// 	p.x = conf->pov->p.x;
// 	p.y = conf->pov->p.y;
// 	p = add_vec(p, vec(conf->pov->angle, conf->pov->mag * -1));
// 	if (p.x > conf->pov->width || p.x < 0 || p.y > conf->pov->height || p.y < 0)
// 		return ;
// 	if (conf->map[(int)(p.y / TILE_SIZE)][(int)(p.x / TILE_SIZE)] != '1')
// 	{
// 		conf->pov->p.y = round(p.y);
// 		conf->pov->p.x = round(p.x);
// 	}
}

static void	move_left(t_app *self)
{
	(void)self;
// 	t_point	p;

// 	p.x = conf->pov->p.x;
// 	p.y = conf->pov->p.y;
// 	p = add_vec(p, vec(conf->pov->angle + r_angle(90), conf->pov->mag));
// 	if (p.x > conf->pov->width || p.x < 0 || p.y > conf->pov->height || p.y < 0)
// 		return ;
// 	if (conf->map[(int)(p.y / TILE_SIZE)][(int)(p.x / TILE_SIZE)] != '1')
// 	{
// 		conf->pov->p.y = round(p.y);
// 		conf->pov->p.x = round(p.x);
// 	}
}

static void	move_right(t_app *self)
{
	(void)self;
// 	t_point	p;

// 	p.x = conf->pov->p.x;
// 	p.y = conf->pov->p.y;
// 	p = add_vec(p, vec(conf->pov->angle - r_angle(90), conf->pov->mag));
// 	if (p.x > conf->pov->width || p.x < 0 || p.y > conf->pov->height || p.y < 0)
// 		return ;
// 	if (conf->map[(int)(p.y / TILE_SIZE)][(int)(p.x / TILE_SIZE)] != '1')
// 	{
// 		conf->pov->p.y = round(p.y);
// 		conf->pov->p.x = round(p.x);
// 	}
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
