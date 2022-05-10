/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 00:56:03 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* TODO: move to libft.h via the libft repo and then use the update script */
t_point	point(double x, double y)
{
	return ((t_point) {x, y});
}

t_point	point_add(t_point a, t_point b)
{
	return (point(a.x + b.x, a.y + b.y));
}

t_point	point_subtract(t_point a, t_point b)
{
	return (point(a.x - b.x, a.y - b.y));
}

t_point	point_multiply(int multiplier, t_point p)
{
	return (point(multiplier * p.x, multiplier * p.y));
}

t_vector	vector(double angle, double size)
{
	return ((t_vector) { trim(angle), size });
}

t_point	point_move(t_point p, t_vector v)
{
	t_point	delta;

	delta = point(cos(v.angle), -sin(v.angle));
	delta = point_multiply(v.size, delta);
	return (point_add(p, delta));
}

t_bool	is_empty_line(char *line)
{
	return (line && ft_streq("", line));
}

t_bool	is_valid_rgb(char **colors)
{
	int	color;

	if (ft_strslen(colors) != 3)
		return (FALSE);
	while (*colors)
	{
		if (!ft_isnumber(*colors))
			return (FALSE);
		color = ft_atoi(*colors++);
		if (color < 0 || color > 255)
			return (FALSE);
	}
	return (TRUE);
}

/* TODO *********** */

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
	parse(&self, argv[1]);
	settings_init(&self);
	player_init(&self);

	self.mlx = mlx_init();
	self.mlx_window = mlx_new_window(self.mlx,
			WIDTH,
			HEIGHT,
			"cub3d!");
	set_image(&self);
	mlx_hook(self.mlx_window, ON_KEYDOWN, 1, key_hook, &self);
	mlx_hook(self.mlx_window, ON_DESTROY, 0, close_app, &self);
	draw(&self);
	mlx_loop(self.mlx);

	return (0);
}
