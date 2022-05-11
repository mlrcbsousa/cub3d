/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:42:56 by josantos          #+#    #+#             */
/*   Updated: 2022/05/11 18:34:29 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// length to wall
double	point_distance(t_point p, t_point q, double a)
{
	return ((q.x - p.x) / cos(a));
}

double	trim(double a)
{
	if (a < 0)
		a += 2 * PI;
	if (a > 2 * PI)
		a -= 2 * PI;
	return (a);
}

int	nearest_tile(double pixel)
{
	return (((int)pixel >> BITS) << BITS);
}

double	fish_bowl(double length, double angle)
{
	return (length * cos(angle));
}

double	get_ray_length_to_wall(t_app *self, int max, t_ray ray,
	t_point offset)
{
	int			i;
	t_point		player;
	t_settings	*s;

	player = self->player->p;
	s = self->settings;
	i = 0;
	while (i < max)
	{
		if (is_element_bounded_and_wall(s, ray.p))
			return (point_distance(player, ray.p, ray.angle));
		ray.p = point_add(ray.p, offset);
		i++;
	}
	return (BIG_LENGTH);
}
