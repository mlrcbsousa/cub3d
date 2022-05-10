/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:19:56 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 20:13:36 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// length to wall
double	point_distance(t_point p, t_point q, double a)
{
	return ((q.x - p.x) / cos(a));
}

int	nearest_tile(double	pixel)
{
	return (((int)pixel >> BITS) << BITS);
}

double	get_ray_length_to_wall(t_app *self, int max, t_point ray,
	t_point offset, double ray_angle)
{
	int			i;
	t_point		player;
	t_settings	*s;

	player = self->player->p;
	s = self->settings;
	i = 0;
	while (i < max)
	{
		if (is_element_bounded_and_wall(s, ray))
		{
			// TODO: add ray x,y to ray struct with length
			return (point_distance(player, ray, ray_angle));
		}
		ray = point_add(ray, offset);
		i++;
	}

	return (BIG_LENGTH);
}

double	get_ray_length_to_horizontal(t_app *self, double ray_angle)
{
	double		aTan;
	t_point		offset;
	t_point		ray;
	t_point		player;

	player = self->player->p;
	aTan = -1 / tan(ray_angle);

	if (ray_angle == 0 || ray_angle == PI)
		return (BIG_LENGTH);

	if (ray_angle > PI) // looking up   TODO: should be less than
	{
		// First intersection
		ray.y = nearest_tile(player.y) - 0.0001;
		ray.x = (player.y - ray.y) * aTan + player.x;
		// TODO: set south wall texture
		offset = point(SIZE * aTan, -SIZE);
	}
	else // if (ray_angle < PI) // looking down
	{
		// First intersection
		ray.y = nearest_tile(player.y) + SIZE;
		ray.x = (player.y - ray.y) * aTan + player.x;
		// TODO: set north wall texture
		offset = point(-SIZE * aTan, SIZE);
	}

	return (get_ray_length_to_wall(self, self->settings->height, ray, offset,
		ray_angle));
}


double	get_ray_length_to_vertical(t_app *self, double ray_angle)
{
	t_point		offset;
	t_point		ray;
	t_point		player;
	double		nTan;

	player = self->player->p;
	nTan = -tan(ray_angle);

	if (ray_angle == PI / 2 || ray_angle == 3 * PI / 2)
		return (BIG_LENGTH);

	if (ray_angle > PI / 2 && ray_angle < 3 * PI / 2) // looking left
	{
		// First intersection
		ray.x = nearest_tile(player.x) - 0.0001;
		ray.y = (player.x - ray.x) * nTan + player.y;
		// TODO: set east wall texture
		offset = point(-SIZE, SIZE * nTan);
	}
	else // if (ray_angle < PI / 2 || ray_angle > 3 * PI / 2) // looking right
	{
		// First intersection
		ray.x = nearest_tile(player.x) + SIZE;
		ray.y = (player.x - ray.x) * nTan + player.y;
		// TODO: set west wall texture
		offset = point(SIZE, -SIZE * nTan);
	}

	return (get_ray_length_to_wall(self, self->settings->width, ray, offset,
		ray_angle));
}

double	get_ray_length(t_app *self, double ray_angle)
{
	double	length_v;
	double	length_h;

	length_h = get_ray_length_to_horizontal(self, ray_angle);
	length_v = get_ray_length_to_vertical(self, ray_angle);

	if (length_v < length_h)
	{
		// TODO: to find out which wall to display
		// ray.x = vx;
		// ray.y = vy;
		g_wall_color = create_trgb(0, 100, 100, 100);
		return (length_v);
	}
	else if (length_v > length_h)
	{
		// ray.x = hx;
		// ray.y = hy;
		g_wall_color = create_trgb(0, 120, 100, 100);
		return (length_h);
	}
	else
		return (length_v);
}

double	fish_bowl(double length, double angle)
{
	return (length * cos(angle));
}

void	raycast(t_app *self)
{
	double		length;
	int			i;
	double		ray_angle;
	t_player	*player;

	player = self->player;
	ray_angle = trim(player->angle + (DR * WIDTH2));
	i = 0;
	while (i < WIDTH)
	{
		length = get_ray_length(self, ray_angle);
		length = fish_bowl(length, player->angle - ray_angle);
		draw_line(self, i, length);
		ray_angle = trim(ray_angle - DR);
		i++;
	}
}

// void	raycasting3d(t_config *conf)
// {
// 	t_ray	ray;
// 	int		column;
//
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
