/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:31:28 by josantos          #+#    #+#             */
/*   Updated: 2022/05/10 23:34:17 by josantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	vector(double angle, double size)
{
	return ((t_vector){trim(angle), size});
}

// t_point	add_vec(t_point p, t_vector v)
// {
// 	t_point	res;

// 	res.x = p.x + (fcos(v.angle) * v.mag);
// 	res.y = p.y - (fsin(v.angle) * v.mag);
// 	return (res);
// }