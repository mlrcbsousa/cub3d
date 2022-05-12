/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:57:42 by msousa            #+#    #+#             */
/*   Updated: 2022/05/12 02:34:09 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	*wall_create(t_app *self, char *path)
{
	t_image	*img;

	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
	{
		ft_putendl_fd("Failed to allocate image memory!", STDERR_FILENO);
		close_app(self);
	}
	img->img = mlx_xpm_file_to_image(self->mlx,
			path,
			&(img->width),
			&(img->height));
	if (!img->img)
	{
		ft_putendl_fd("Failed to load xpm file!", STDERR_FILENO);
		close_app(self);
	}
	img->addr = mlx_get_data_addr(img->img,
			&(img->bits_per_pixel),
			&(img->line_length),
			&(img->endian));
	return (img);
}

void	walls_create(t_app *self)
{
	t_settings	*s;

	s = self->settings;
	s->walls[WALL_NORTH] = wall_create(self, s->paths[WALL_NORTH]);
	s->walls[WALL_SOUTH] = wall_create(self, s->paths[WALL_SOUTH]);
	s->walls[WALL_EAST] = wall_create(self, s->paths[WALL_EAST]);
	s->walls[WALL_WEST] = wall_create(self, s->paths[WALL_WEST]);
}
