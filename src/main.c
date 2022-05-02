/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/05/02 20:08:17 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO: move to libft.h
// use WITH dot
t_bool	ft_isfile_ext(char *filename, char *extension)
{
	unsigned int	len_filename;
	unsigned int	len_extension;

	len_filename = ft_strlen(filename);
	len_extension = ft_strlen(extension);

	// filename smaller then extension length
	if (len_filename <= len_extension)
		return (FALSE);

	return (ft_streq(filename + len_filename - len_extension, extension));
}

t_bool	ft_isfile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	close(fd);
	return (TRUE);
}
// TODO: move to libft.h

static void	set_image(t_app *self)
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

static t_bool	invalid(int argc, char *argv[])
{
	if (argc != 2)
	{
		print_error(NULL, "wrong number of arguments");
		return (TRUE);
	}
	else if (!ft_isfile_ext(argv[1], ".cub"))
	{
		print_error(argv[1], "file argument must be in *.cub format");
		return (TRUE);
	}
	else if (!ft_isfile(argv[1]))
	{
		print_errno(argv[1]);
		return (TRUE);
	}
	// TODO: test the whole cubfile from here
	/*
	 * On the cubfile elements
	 * - Textures are a file that doesnt exist or not a xpm file.
	 * - There are multiple textures for the same wall (north wall texture).
	 * - RGBs dont have 3 numbers, are separated by an invalid character (not a comma) or have values below 0 or above 255.
	 * - There are invalid characters in the cub.
	 *
	 * On the cubfile map
	 * - Multiple players or no player.
	 * - invalid characters !{ ' ', '\t', '0', '1', 'N', 'S', 'E', 'W' }
	 * - Map not closed, check if each map character has no space character around it
	 */
	return (FALSE);
}

static void	usage(void)
{
	ft_putendl_fd(NULL, STDOUT_FILENO);
	ft_putendl_fd("Usage: ./cub3d <map>", STDOUT_FILENO);
	ft_putendl_fd(NULL, STDOUT_FILENO);
	ft_putendl_fd("   - map		Path to *.cub file", STDOUT_FILENO);
	ft_putendl_fd(NULL, STDOUT_FILENO);
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_app		self;

	if (invalid(argc, argv))
		usage();
	game_init(&self, argv[1]);

	self.mlx = mlx_init();
	self.mlx_window = mlx_new_window(self.mlx,
			WIDTH,
			HEIGHT,
			"cub3d!");
	set_image(&self);
	set_hooks(&self);
	draw(&self);
	mlx_loop(self.mlx);

	return (0);
}
