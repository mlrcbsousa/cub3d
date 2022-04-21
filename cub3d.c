/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/04/21 11:33:04 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_image(t_app *self)
{
	t_image	*img;

	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
	{
		ft_putendl_fd("Failed to allocate image memory!", 2);
		exit(1);
	}
	img->img = mlx_new_image(self->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img,
			&(img->bits_per_pixel),
			&(img->line_length),
			&(img->endian));
	self->img = img;
}

int	main(int argc, char *argv[], char *env[])
{
	t_app		self;

	(void)argc;
	(void)argv;
	(void)env;

	self.mlx = mlx_init();
	self.mlx_window = mlx_new_window(self.mlx,
			WIDTH,
			HEIGHT,
			"Hello world!");
	set_image(&self);
	set_hooks(&self);
	draw(&self);
	mlx_loop(self.mlx);

	return (0);
}
