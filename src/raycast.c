/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:19:56 by msousa            #+#    #+#             */
/*   Updated: 2022/05/11 18:05:05 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_ray_length_to_wall(t_app *self, int max, t_ray ray,
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
		{
			// TODO: add ray.p x,y to ray.p struct with length
			return (point_distance(player, ray.p, ray.angle));
		}
		ray.p = point_add(ray.p, offset);
		i++;
	}
	return (BIG_LENGTH);
}

static double	get_ray_length_to_horizontal(t_app *self, t_ray ray)
{
	double		a_tan;
	t_point		offset;
	// t_point		ray;
	t_point		player;

	player = self->player->p;
	a_tan = -1 / tan(ray.angle);
	if (ray.angle == 0 || ray.angle == PI)
		return (BIG_LENGTH);
	if (ray.angle > PI) // looking up   TODO: should be less than
	{
		ray.p.y = nearest_tile(player.y) - 0.0001;
		ray.p.x = (player.y - ray.p.y) * a_tan + player.x;
		offset = point(SIZE * a_tan, -SIZE);
	}
	else
	{
		ray.p.y = nearest_tile(player.y) + SIZE;
		ray.p.x = (player.y - ray.p.y) * a_tan + player.x;
		offset = point(-SIZE * a_tan, SIZE);
	}
	return (get_ray_length_to_wall(self, self->settings->height, ray, offset));
}

static double	get_ray_length_to_vertical(t_app *self, t_ray ray)
{
	t_point		offset;
	t_point		player;
	double		n_tan;

	player = self->player->p;
	n_tan = -tan(ray.angle);

	if (ray.angle == PI / 2 || ray.angle == 3 * PI / 2)
		return (BIG_LENGTH);

	if (ray.angle > PI / 2 && ray.angle < 3 * PI / 2)
	{
		ray.p.x = nearest_tile(player.x) - 0.0001;
		ray.p.y = (player.x - ray.p.x) * n_tan + player.y;
		offset = point(-SIZE, SIZE * n_tan);
	}
	else
	{
		ray.p.x = nearest_tile(player.x) + SIZE;
		ray.p.y = (player.x - ray.p.x) * n_tan + player.y;
		offset = point(SIZE, -SIZE * n_tan);
	}

	return (get_ray_length_to_wall(self, self->settings->width, ray, offset));
}

static double	get_ray_length(t_app *self, t_ray ray)
{
	double	length_v;
	double	length_h;

	length_h = get_ray_length_to_horizontal(self, ray);
	length_v = get_ray_length_to_vertical(self, ray);

	if (length_v < length_h)
		return (length_v);
	else
		return (length_h);
}

t_wall	get_ray_wall(t_app *self, t_ray ray)
{
	if (ray.length == get_ray_length_to_vertical(self, ray))
	{
		if (ray.angle > PI / 2 && ray.angle < 3 * PI / 2)
			return (WALL_EAST);
		else
			return (WALL_WEST);
	}
	else
	{
		if (ray.angle > PI)
			return (WALL_SOUTH);
		else
			return (WALL_NORTH);
	}
}

void	raycast(t_app *self)
{
	int			i;
	t_player	*player;
	t_ray		ray;

	player = self->player;
	ray.wall = WALL_NULL;
	ray.angle = trim(player->angle - (DR * WIDTH2));
	i = 0;
	while (i < WIDTH)
	{
		ray.length = get_ray_length(self, ray);
		ray.wall = get_ray_wall(self, ray);
		ray.length = fish_bowl(ray.length, player->angle - ray.angle);
		draw_line(self, i, ray);
		ray.angle = trim(ray.angle + DR);
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
