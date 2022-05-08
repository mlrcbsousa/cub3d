/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:19:56 by msousa            #+#    #+#             */
/*   Updated: 2022/05/09 00:14:50 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	distance(t_point p, t_point q, float a)
{
	(void)a;
	return (sqrt((q.x - p.x) * (q.x - p.x) + (q.y - p.y) * (q.y - p.y)));
}

void	draw_rays(t_app *self)
{
	int r, mx, my, dof; // depth of field
	// mx: map x, my: map y
	float rx, ry, ra, xo, yo, distT;
	t_player	*p;
	t_settings	*settings;
	char**		map;

	p = self->player;
	settings = self->settings;
	map = settings->map;
	ra = p->a - DR * (WIDTH / 2);
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;

	r = 0;
	while (r < WIDTH)
	{
		// check horizontal lines
		dof = 0;
		float	distH = 1000000, hx = p->x, hy = p->y;
		float	aTan = -1 / tan(ra);

		// First intersection

		// check direction up or down
		if (ra > PI) // looking up
		{
			ry = (((int)p->y >> 6) << 6) - 0.0001;
			rx = (p->y - ry) * aTan + p->x;
			yo = -TILE_SIZE;
			xo = -yo * aTan;
		}
		if (ra < PI) // looking down
		{
			ry = (((int)p->y >> 6) << 6) + TILE_SIZE;
			rx = (p->y - ry) * aTan + p->x;
			yo = TILE_SIZE;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI) // straight looking left or right
		{
			ry = p->y;
			rx = p->x;
			dof = settings->height; // to not loop
		}

		// loop to find next
		while(dof < settings->height)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (mx > 0 && my > 0 && mx < settings->width
				&& my < settings->height
				&& map[mx][my] == MAP_WALL)
			{
				hx = rx;
				hy = ry;
				distH = distance((t_point){p->x, p->y}, (t_point){hx, hy}, ra);
				dof = settings->height; // end loop
			}
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}


		// check vertical lines
		dof = 0;
		float	distV = 1000000, vx = p->x, vy = p->y;
		float	nTan = -tan(ra);

		// First intersection

		// check direction left or right
		if (ra > PI / 2 && ra < 3 * PI / 2) // looking left
		{
			rx = (((int)p->x >> 6) << 6) - 0.0001;
			ry = (p->x - rx) * nTan + p->y;
			xo = -TILE_SIZE;
			yo = -xo * nTan;
		}
		if (ra < PI / 2 || ra > 3 * PI / 2) // looking right
		{
			rx = (((int)p->x >> 6) << 6) + TILE_SIZE;
			ry = (p->x - rx) * nTan + p->y;
			xo = TILE_SIZE;
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
			{
				vx = rx;
				vy = ry;
				distV = distance((t_point){p->x, p->y}, (t_point){vx, vy}, ra);
				dof = settings->width; // end loop
			}
			else
			{
				rx += xo; // next line
				ry += yo;
				dof++;
			}
		}

		if (distV < distH)
		{
			rx = vx;
			ry = vy;
			distT = distV;
		}
		if (distV > distH)
		{
			rx = hx;
			ry = hy;
			distT = distH;
		}

		// Draw 3d scene
		float	lineH = (TILE_SIZE * HEIGHT) / distT; // line height
		if (lineH > HEIGHT)
			lineH = HEIGHT;
		float	lineO = HEIGHT / 2 - lineH / 2; // line offset

		// draw y line mlx
		draw_line(self, r, lineH, lineO);

		ra += DR;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
		r++;
	}
}
