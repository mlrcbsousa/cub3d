/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:13:41 by josantos          #+#    #+#             */
/*   Updated: 2022/05/10 23:34:34 by josantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	point(double x, double y)
{
	return ((t_point){x, y});
}

t_point	point_add(t_point a, t_point b)
{
	return (point(a.x + b.x, a.y + b.y));
}

t_point	point_subtract(t_point a, t_point b)
{
	return (point(a.x - b.x, a.y - b.y));
}

t_point	point_multiply(int multiplier, t_point p)
{
	return (point(multiplier * p.x, multiplier * p.y));
}

t_point	point_move(t_point p, t_vector v)
{
	t_point	delta;

	delta = point(cos(v.angle), -sin(v.angle));
	delta = point_multiply(v.size, delta);
	return (point_add(p, delta));
}
