/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:06:29 by msousa            #+#    #+#             */
/*   Updated: 2022/05/12 00:35:42 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
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

int	get_wall_color(t_app *self, t_ray ray, int j, int wall_offset)
{
	t_settings	*settings;
	t_point		delta;
	int			x;
	double			y;

	settings = self->settings;
	delta = point(cos(ray.angle), sin(ray.angle));
	delta = point_multiply(ray.length, delta);
	delta = point_add(self->player->p, delta);

	if (ray.wall == WALL_EAST || ray.wall == WALL_WEST)
		x = (int)(floor(delta.y + 1)) % SIZE;
	else
		x = (int)(floor(delta.x + 1)) % SIZE;

	// printf("%d, %d, %d\n", j, wall_offset, ray.height);
	y = (((j - wall_offset) * SIZE) / ray.height);
	// y = y * SIZE;

	// printf("(%d, %f)\n", x, y);
	// printf("(%d, %d)\n", x, y);
	return (get_texture_color(settings->walls[ray.wall], x, y));
}

void	draw_line(t_app *self, int i, t_ray ray)
{
	int	j;
	int	color;
	int	wall_offset;
	double	length;
	// int	height;

	// length needed before fishbowl to calculate texture map
	length = fish_bowl(ray.length, self->player->angle - ray.angle);
	ray.height = (int)((SIZE * HEIGHT) / length); // line height
	if (ray.height > HEIGHT)
		ray.height = HEIGHT;
	wall_offset = (int)(HEIGHT2 - (ray.height / 2)); // line offset
	j = 0;
	while (j < wall_offset)
	{
		color = self->settings->color_ceiling;
		my_mlx_pixel_put(self->img, i, j, color);
		j++;
	}
	while (j < wall_offset + ray.height)
	{
		color = get_wall_color(self, ray, j, wall_offset);
		my_mlx_pixel_put(self->img, i, j, color);
		j++;
	}
	while (j < HEIGHT)
	{
		color = self->settings->color_floor;
		my_mlx_pixel_put(self->img, i, j, color);
		j++;
	}
}

void	set_image(t_app *self)
{
	t_image	*img;

	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
	{
		ft_putendl_fd("Failed to allocate image memory!", STDERR_FILENO);
		exit(1);
	}
	img->img = mlx_new_image(self->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img,
			&(img->bits_per_pixel),
			&(img->line_length),
			&(img->endian));
	self->img = img;
}
