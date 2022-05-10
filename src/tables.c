/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:41:39 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 16:31:01 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double arc_to_rad(double arc_angle)
{
	return ((double)(arc_angle * PI)/(double)ANGLE180);
}

void	tables_init(t_app *self)
{
	t_tables	t_;
	int			i;
	double		radian;

	t_ = self->tables;
	i = 0;
	while (i <= ANGLE360)
	{
		// get the radian value (the last addition is to avoid division by 0,
		// try removing that and you'll see a hole in the wall when a ray is
		// at 0, 90, 180, or 270 degree)
		radian = arc_to_rad(i) + 0.0001;

		// init trigonometry tables
		t_.sin[i] = sin(radian);
		t_.sin_i[i] = 1.0 / t_.sin[i];
		t_.cos[i] = cos(radian);
		t_.cos_i[i] = 1.0 / t_.cos[i];
		t_.tan[i] = tan(radian);
		t_.tan_i[i] = 1.0 / t_.tan[i];

		// init offset tables

        //  you can see that the distance between xi is the same
        //  if we know the angle
        //  _____|_/next xi______________
        //       |
        //  ____/|next xi_________   slope = tan = height / dist between xi's
        //     / |
        //  __/__|_________  dist between xi = height/tan where height=tile size
        // old xi|
        //                  distance between xi = x_step[view_angle];
        //

		// facing left
		if (i >= ANGLE90 && i < ANGLE270)
		{
			t_.step_x[i] = SIZE / t_.tan[i];
			if (t_.step_x[i] > 0)
				t_.step_x[i] =- t_.step_x[i];
		}
		// facing right
		else
		{
			t_.step_x[i] = SIZE / t_.tan[i];
			if (t_.step_x[i] < 0)
				t_.step_x[i] =- t_.step_x[i];
		}

		// facing down
		// TODO: isnt this facing up??
		if (i >= ANGLE0 && i < ANGLE180)
		{
			t_.step_y[i] = SIZE * t_.tan[i];
			if (t_.step_y[i] < 0)
				t_.step_y[i] =- t_.step_y[i];
		}
		// facing up
		else
		{
			t_.step_y[i] = SIZE * t_.tan[i];
			if (t_.step_y[i] > 0)
				t_.step_y[i] =- t_.step_y[i];
		}

		i++;
	}

	// init fish table
	i = -ANGLE30;
	while (i <= ANGLE30)
	{
		radian = arc_to_rad(i);
        // we don't have negative angle, so make it start at 0
		t_.fish[i + ANGLE30] = 1.0 / cos(radian);
		i++;
	}
}
