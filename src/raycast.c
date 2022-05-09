/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:19:56 by msousa            #+#    #+#             */
/*   Updated: 2022/05/09 19:33:54 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// length to wall
float	point_distance(t_point p, t_point q, float a)
{
	(void)a;
	return (sqrt((q.x - p.x) * (q.x - p.x) + (q.y - p.y) * (q.y - p.y)));
	// return ((q.x - p.x) / cos(a));
}

float	trim(float a)
{
	if (a < 0)
		a += 2 * PI;
	if (a > 2 * PI)
		a -= 2 * PI;
	return (a);
}

// void	raycasting3d(t_config *conf)
// {
// 	t_ray	ray;
// 	int		column;

// 	ray.angle = r_angle(30);
// 	column = 0;
// 	while (ray.angle > -r_angle(30) && column < WIN_W)
// 	{
// 		ray.dist_wall = magic_length(conf, ray.angle);
// 		ray.end = add_vec(conf->pov->p,
// 				vec((ray.angle + conf->pov->angle), ray.dist_wall));
// 		ray.color = set_wall_color(ray.dist_wall,
// 				conf->pov->angle + ray.angle, conf);
// 		ray.height = ray.dist_wall * fcos(abs(ray.angle));
// 		ray.height = ((double)TILE_SIZE / ray.height) * conf->pov->dtp;
// 		draw_line(conf, ray, column);
// 		column++;
// 		ray.angle--;
// 	}
// }

// struct	s_ray
// {
// 	double	length;
// 	t_point	end;
// 	t_wall	wall;
// 	int		height;
// 	double	angle;
// };

// sudo
// - find length
// 	- vertical distance
// 	- horizontal distance
//	- turn into length
// 	- pick
// - pick wall
// - fish bowl
// - draw line


int	nearest_tile(double	pixel)
{
	return (((int)pixel >> BITS) << BITS);
}

float	get_ray_length_to_horizontal(t_app *self, float ray_angle)
{
	// check horizontal lines
	int 	dof;
	float	hx;
	float	hy;
	float	aTan;
	int		map_x;
	int		map_y;
	float	ray_x;
	float	ray_y;
	float	offset_x;
	float	offset_y;
	float 	length;

	t_player	*p;
	t_settings	*s;
	char**		map;

	p = self->player;
	s = self->settings;
	map = s->map;

	dof = 0;
	length = 1000000;
	hx = p->x;
	hy = p->y;
	aTan = -1 / tan(ray_angle);

	// First intersection

	// check direction up or down
	if (ray_angle > PI) // looking up
	{
		ray_y = nearest_tile(p->y) - 0.0001;
		ray_x = (p->y - ray_y) * aTan + p->x;
		offset_y = -SIZE;
		offset_x = -offset_y * aTan;
	}
	if (ray_angle < PI) // looking down
	{
		ray_y = nearest_tile(p->y) + SIZE;
		ray_x = (p->y - ray_y) * aTan + p->x;
		offset_y = SIZE;
		offset_x = -offset_y * aTan;
	}
	if (ray_angle == 0 || ray_angle == PI) // straight looking left or right
	{
		ray_y = p->y;
		ray_x = p->x;
		length = 1000000;
		dof = s->height; // to not loop
	}

	// loop to find next
	while (dof < s->height)
	{
		map_x = (int)(ray_x) >> BITS;
		map_y = (int)(ray_y) >> BITS;
		if (map_x > 0 && map_y > 0 && map_x < s->width
			&& map_y < s->height
			&& map[map_x][map_y] == MAP_WALL)
		{
			hx = ray_x;
			hy = ray_y;
			length = point_distance((t_point){p->x, p->y}, (t_point){hx, hy}, ray_angle);
			dof = s->height; // end loop
		}
		else
		{
			ray_x += offset_x;
			ray_y += offset_y;
			dof++;
		}
	}
	return (length);
}


float	get_ray_length_to_vertical(t_app *self, float ray_angle)
{
	float	vx;
	float	vy;
	float	nTan;
	int		map_x;
	int		map_y;
	float	ray_x;
	float	ray_y;
	float	offset_x;
	float	offset_y;
	int 	dof;
	float 	length;

	t_player	*p;
	t_settings	*s;
	char**		map;

	p = self->player;
	s = self->settings;
	map = s->map;

	// check vertical lines
	dof = 0;
	length = 1000000;
	vx = p->x;
	vy = p->y;
	nTan = -tan(ray_angle);

	// First intersection

	// check direction left or right
	if (ray_angle > PI / 2 && ray_angle < 3 * PI / 2) // looking left
	{
		ray_x = nearest_tile(p->x) - 0.0001;
		ray_y = (p->x - ray_x) * nTan + p->y;
		offset_x = -SIZE;
		offset_y = -offset_x * nTan;
	}
	if (ray_angle < PI / 2 || ray_angle > 3 * PI / 2) // looking right
	{
		ray_x = nearest_tile(p->x) + SIZE;
		ray_y = (p->x - ray_x) * nTan + p->y;
		offset_x = SIZE;
		offset_y = -offset_x * nTan;
	}
	if (ray_angle == 0 || ray_angle == PI) // straight looking up or down
	{
		ray_y = p->y;
		ray_x = p->x;
		length = 1000000;
		dof = s->width;
	}

	// loop to find next
	while (dof < s->width)
	{
		map_x = (int)(ray_x) >> BITS;
		map_y = (int)(ray_y) >> BITS;
		if (map_x > 0 && map_y > 0 && map_x < s->width
			&& map_y < s->height
			&& map[map_x][map_y] == MAP_WALL)
		{
			vx = ray_x;
			vy = ray_y;
			length = point_distance((t_point){p->x, p->y}, (t_point){vx, vy}, ray_angle);
			dof = s->width; // end loop
		}
		else
		{
			ray_x += offset_x; // next line
			ray_y += offset_y;
			dof++;
		}
	}
	return (length);
}

float	get_ray_length(t_app *self, float ray_angle)
{
	float	length_v;
	float	length_h;

	length_h = get_ray_length_to_horizontal(self, ray_angle);
	length_v = get_ray_length_to_vertical(self, ray_angle);

	if (length_v < length_h)
	{
		// TODO: to find out which wall
		// ray_x = vx;
		// ray_y = vy;
		g_wall_color = create_trgb(0, 100, 100, 100);
		return (length_v);
	}
	else if (length_v > length_h)
	{
		// ray_x = hx;
		// ray_y = hy;
		g_wall_color = create_trgb(0, 120, 100, 100);
		return (length_h);
	}
	else
		return (HEIGHT);
}

double	fish_bowl(double length, double angle)
{
	return (length * cos(angle));
}

void	raycast(t_app *self)
{
	float		length;
	int			i;
	float		ray_angle;
	t_player	*p;
	int			wall_height;
	int			wall_offset;

	p = self->player;
	ray_angle = trim(p->a - (DR * WIDTH / 2));
	i = 0;
	while (i < WIDTH)
	{
		length = get_ray_length(self, ray_angle);
		length = fish_bowl(length, p->a - ray_angle);

		wall_height = (int)((SIZE * HEIGHT) / length); // line height
		if (wall_height > HEIGHT)
			wall_height = HEIGHT;
		wall_offset = (int)((HEIGHT / 2) - (wall_height / 2)); // line offset

		draw_line(self, i, wall_height, wall_offset);

		// increment
		ray_angle = trim(ray_angle + DR);
		i++;
	}
}
