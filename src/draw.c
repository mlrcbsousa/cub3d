/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:06:29 by msousa            #+#    #+#             */
/*   Updated: 2022/05/09 17:34:40 by msousa           ###   ########.fr       */
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

void	draw_line(t_app *self, int ray, int line_height, int line_offset)
{
	int	j;
	int	color;

	j = 0;
	while (j < line_offset)
	{
		color = self->settings->color_ceiling;
		my_mlx_pixel_put(self->img, ray, j, color);
		j++;
	}
	while (j < line_offset + line_height)
	{
		// TODO: decide which wall to paint
		my_mlx_pixel_put(self->img, ray, j, g_wall_color);
		j++;
	}
	while (j < HEIGHT)
	{
		color = self->settings->color_floor;
		my_mlx_pixel_put(self->img, ray, j, color);
		j++;
	}
}
