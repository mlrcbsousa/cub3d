/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:19:56 by msousa            #+#    #+#             */
/*   Updated: 2022/05/09 21:28:18 by msousa           ###   ########.fr       */
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
	int 		i;
	float		aTan;
	int			map_x;
	int			map_y;
	float 		length;
	t_point		offset;
	t_point		ray;
	t_point		wall;
	t_point		player;
	t_settings	*s;
	char**		map;

	player = self->player->p;
	s = self->settings;
	map = s->map;
	length = BIG_LENGTH;
	wall = player;
	aTan = -1 / tan(ray_angle);

	if (ray_angle == 0 || ray_angle == PI)
		return (length);

	if (ray_angle > PI) // looking up
	{
		// First intersection
		ray.y = nearest_tile(player.y) - 0.0001;
		ray.x = (player.y - ray.y) * aTan + player.x;
		offset = point(SIZE * aTan, -SIZE);
	}
	else if (ray_angle < PI) // looking down
	{
		// First intersection
		ray.y = nearest_tile(player.y) + SIZE;
		ray.x = (player.y - ray.y) * aTan + player.x;
		offset = point(-SIZE * aTan, SIZE);
	}

	i = 0;
	while (i < s->height)
	{
		map_x = (int)(ray.x) >> BITS;
		map_y = (int)(ray.y) >> BITS;
		if (map_x > 0 && map_y > 0 && map_x < s->width
			&& map_y < s->height
			&& map[map_x][map_y] == MAP_WALL)
		{
			wall = ray;
			length = point_distance(player, wall, ray_angle);
			break ;
		}

		ray = point_add(ray, offset);
		i++;
	}
	return (length);
}


float	get_ray_length_to_vertical(t_app *self, float ray_angle)
{
	int 		i;
	int			map_x;
	int			map_y;
	float 		length;
	t_point		offset;
	t_point		ray;
	t_point		wall;
	t_point		player;
	t_settings	*s;
	char**		map;
	float		nTan;

	player = self->player->p;
	s = self->settings;
	map = s->map;
	length = BIG_LENGTH;
	wall = player;
	nTan = -tan(ray_angle);

	if (ray_angle == PI / 2 || ray_angle == 3 * PI / 2) // straight looking up or down
		return (length);

	// check direction left or right
	if (ray_angle > PI / 2 && ray_angle < 3 * PI / 2) // looking left
	{
		// First intersection
		ray.x = nearest_tile(player.x) - 0.0001;
		ray.y = (player.x - ray.x) * nTan + player.y;
		offset = point(-SIZE, SIZE * nTan);
	}
	else if (ray_angle < PI / 2 || ray_angle > 3 * PI / 2) // looking right
	{
		// First intersection
		ray.x = nearest_tile(player.x) + SIZE;
		ray.y = (player.x - ray.x) * nTan + player.y;
		offset = point(SIZE, -SIZE * nTan);
	}

	i = 0;
	while (i < s->width)
	{
		map_x = (int)(ray.x) >> BITS;
		map_y = (int)(ray.y) >> BITS;
		if (map_x > 0 && map_y > 0 && map_x < s->width
			&& map_y < s->height
			&& map[map_x][map_y] == MAP_WALL)
		{
			wall = ray;
			length = point_distance(player, wall, ray_angle);
			break ;
		}
		ray = point_add(ray, offset);
		i++;
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
		return (length_v); // return (HEIGHT);
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
	t_player	*player;
	int			wall_height;
	int			wall_offset;

	player = self->player;
	ray_angle = trim(player->a - (DR * WIDTH / 2));
	i = 0;
	while (i < WIDTH)
	{
		length = get_ray_length(self, ray_angle);
		length = fish_bowl(length, player->a - ray_angle);

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
