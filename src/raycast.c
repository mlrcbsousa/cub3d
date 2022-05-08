/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:19:56 by msousa            #+#    #+#             */
/*   Updated: 2022/05/08 20:47:39 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// float

void	draw_rays(t_app *self)
{
	int r, mx, my, mp, dof; // depth of field
	// mx: map x, my: map y
	float rx, ry, ra, xo, yo;
	t_player	*p;
	t_settings	*settings;
	char**		map;

	p = self->player;
	settings = self->settings;
	map = settings->map;
	ra = p->a;

	// WIDTH / 60;
	r = 0;
	while (r < 1)
	{
		// check horizontal lines
		dof = 0;
		float aTan = -1 / tan(ra);

		// First intersection

		// check direction up or down
		if (ra > PI) // looking up
		{
			ry = (((int)p->y >> 6) << 6) - 0.0001;
			rx = (p->y - ry) * aTan + p->x;
			yo = -MAP_SIZE;
			xo = -yo * aTan;
		}
		if (ra < PI) // looking down
		{
			ry = (((int)p->y >> 6) << 6) + MAP_SIZE;
			rx = (p->y - ry) * aTan + p->x;
			yo = MAP_SIZE;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI) // straight looking left or right
		{
			ry = p->y;
			rx = p->x;
			dof = settings->width;
		}

		// loop to find next
		while(dof < settings->width)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (mx > 0 && my > 0 && mx < settings->width
				&& my < settings->height
				&& map[mx][my] == MAP_WALL)
				dof = settings->width; // end loop
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}


		// check vertical lines
		dof = 0;
		float nTan = -tan(ra);

		// First intersection

		// check direction left or right
		if (ra > PI / 2 && ra < 3 * PI / 2) // looking left
		{
			rx = (((int)p->x >> 6) << 6) - 0.0001;
			ry = (p->x - rx) * nTan + p->y;
			xo = -MAP_SIZE;
			yo = -xo * nTan;
		}
		if (ra < PI / 2 || ra > 3 * PI / 2) // looking right
		{
			rx = (((int)p->x >> 6) << 6) + MAP_SIZE;
			ry = (p->x - rx) * nTan + p->y;
			xo = MAP_SIZE;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI) // straight looking up or down
		{
			ry = p->y;
			rx = p->x;
			dof = settings->width;
		}

		// loop to find next
		while(dof < settings->width)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (mx > 0 && my > 0 && mx < settings->width
				&& my < settings->height
				&& map[mx][my] == MAP_WALL)
				dof = settings->width; // end loop
			else
			{
				rx += xo; // next line
				ry += yo;
				dof++;
			}
		}


		r++;
	}
}
