/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/05/11 22:34:12 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_app		self;

	if (invalid(argc, argv))
		usage();
	parse(&self, argv[1]);
	settings_init(&self);
	player_init(&self);
	self.mlx = mlx_init();
	self.mlx_window = mlx_new_window(self.mlx,
			WIDTH,
			HEIGHT,
			"cub3d!");
	set_image(&self);
	walls_create(&self);
	mlx_hook(self.mlx_window, ON_KEYDOWN, 1, key_hook, &self);
	mlx_hook(self.mlx_window, ON_DESTROY, 0, close_app, &self);
	draw(&self);
	mlx_loop(self.mlx);
	return (0);
}
