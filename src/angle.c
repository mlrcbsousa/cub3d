/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:13:15 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 20:56:36 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	trim(double a)
{
	if (a < 0)
		a += ANGLE360;
	else if (a > ANGLE360)
		a -= ANGLE360;
	return (a);
}

double arc_to_rad(double arc_angle)
{
	return ((double)(arc_angle * PI)/(double)ANGLE180);
}
