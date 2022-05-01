/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 18:38:35 by msousa            #+#    #+#             */
/*   Updated: 2022/05/01 21:13:54 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	valid_game_element(char *line)
{
	(void)line;
	return (TRUE);
}

void	set_game_element(char *line, t_app *self)
{
	(void)line;
	(void)self;
}

int	set_game_elements(int fd, t_app *self)
{
	int		status;
	char	*line;

	status = 1;
	line = NULL;
	while (status > 0)
	{
		status = get_next_line(fd, &line);
		if (line)
			printf("%s\n", line);

		// TODO: game elements come first
		if (valid_game_element(line))
			set_game_element(line, self);

		// TODO: map comes last
		// so must have all elements before starting map parsing
	}
	if (status < 0)
		return (EXIT_FAILURE);
	return (status);
}

void	game_init(t_app *self, char* cubfile)
{
	// t_walls	*walls;
	int	status;

	self->img = NULL;
	self->mlx_window = NULL;
	self->mlx = NULL;
	self->color_floor = -1;
	self->color_ceiling = -1;
	self->walls = NULL;
	status = file_open(cubfile, self, set_game_elements);
	if (status)
		exit(status);
}

void	game_loop(t_app *self)
{
	(void)self;
}

void	game_destroy(t_app *self)
{
	if (self->walls)
		free(self->walls);
}
