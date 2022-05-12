/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:06:29 by msousa            #+#    #+#             */
/*   Updated: 2022/05/12 02:20:52 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw(t_app *self)
{
	raycast(self);
	mlx_put_image_to_window(self->mlx, self->mlx_window, self->img->img, 0, 0);
}

unsigned int	get_texture_color(t_image *wall, int x, int y)
{
	return (*(unsigned int *)((wall->addr
			+ (y * wall->line_length) + (x * wall->bits_per_pixel / 8))));
}

int	get_wall_color(t_app *self, t_ray ray, int j)
{
	t_settings	*settings;
	t_point		delta;
	int			x;
	int			y;
	int			offset;

	settings = self->settings;
	delta = point(cos(ray.angle), sin(ray.angle));
	delta = point_multiply(ray.length, delta);
	delta = point_add(self->player->p, delta);
	if (ray.wall == WALL_EAST || ray.wall == WALL_WEST)
		x = (int)(floor(delta.y + 1)) % SIZE;
	else
		x = (int)(floor(delta.x + 1)) % SIZE;
	offset = (int)(HEIGHT2 - (ray.height / 2));
	y = (((j - offset) * SIZE) / ray.height);
	return (get_texture_color(settings->walls[ray.wall], x, y));
}
