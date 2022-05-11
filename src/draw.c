/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:06:29 by msousa            #+#    #+#             */
/*   Updated: 2022/05/11 17:34:06 by msousa           ###   ########.fr       */
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

void	draw_line(t_app *self, int i, t_ray ray)
{
	int	j;
	int	color;
	int	line_height;
	int	line_offset;

	line_height = (int)((SIZE * HEIGHT) / ray.length); // line height
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	line_offset = (int)(HEIGHT2 - (line_height / 2)); // line offset
	j = 0;
	while (j < line_offset)
	{
		color = self->settings->color_ceiling;
		my_mlx_pixel_put(self->img, i, j, color);
		j++;
	}
	while (j < line_offset + line_height)
	{
		if (ray.wall == WALL_NORTH || ray.wall == WALL_SOUTH)
			color = create_trgb(0, 100, 100, 100);
		else
			color = create_trgb(0, 120, 100, 100);
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
