/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:19:17 by msousa            #+#    #+#             */
/*   Updated: 2022/05/12 02:33:23 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel_ceiling(int i, int *j, int wall_offset, t_app *self)
{
	while (*j < wall_offset)
	{
		my_mlx_pixel_put(self->img, i, *j, self->settings->color_ceiling);
		*j += 1;
	}
}

static void	put_pixel_floor(int i, int *j, t_app *self)
{
	while (*j < HEIGHT)
	{
		my_mlx_pixel_put(self->img, i, *j, self->settings->color_floor);
		*j += 1;
	}
}

void	draw_line(t_app *self, int i, t_ray ray)
{
	int		j;
	int		color;
	double	length;
	int		wall_offset;
	int		wall_height;

	length = fish_bowl(ray.length, self->player->angle - ray.angle);
	ray.height = (int)((SIZE * HEIGHT) / length);
	wall_height = ray.height;
	if (ray.height > HEIGHT)
		wall_height = HEIGHT;
	wall_offset = (int)(HEIGHT2 - (wall_height / 2));
	j = 0;
	put_pixel_ceiling(i, &j, wall_offset, self);
	while (j < wall_offset + wall_height)
	{
		color = get_wall_color(self, ray, j);
		my_mlx_pixel_put(self->img, i, j, color);
		j++;
	}
	put_pixel_floor(i, &j, self);
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
