/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:42:56 by josantos          #+#    #+#             */
/*   Updated: 2022/05/11 00:33:56 by josantos         ###   ########.fr       */
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
