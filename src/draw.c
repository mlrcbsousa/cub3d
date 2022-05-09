/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:06:29 by msousa            #+#    #+#             */
/*   Updated: 2022/05/09 01:23:14 by msousa           ###   ########.fr       */
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
	// int	i;
	// int	j;
	// int	color;

	// i = 0;
	// while (i < WIDTH)
	// {
	// 	j = 0;
	// 	while (j < HEIGHT)
	// 	{
	// 		color = create_trgb(0, 0, 0, 0);
	// 		my_mlx_pixel_put(self->img, i, j, color);
	// 		j++;
	// 	}
	// 	i++;
	// }
	draw_rays(self);
	mlx_put_image_to_window(self->mlx, self->mlx_window, self->img->img, 0, 0);
}


void	draw_line(t_app *self, int ray, float line_height, float line_offset)
{
	// printf("drawing line\n");
	// printf("ray: %d, line_height: %f, line_offset: %f\n", ray, line_height, line_offset);

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
		// TODO: decide which wall to point
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
