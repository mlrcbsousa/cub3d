/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 18:38:35 by msousa            #+#    #+#             */
/*   Updated: 2022/05/02 21:10:59 by msousa           ###   ########.fr       */
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

t_bool	are_walls_set(t_app *self)
{
	t_walls	*walls;

	walls = self->walls;
	if (walls)
		return (walls->east && walls->north && walls->south && walls->west);
	return (FALSE);
}

int	set_game_mapline(int fd, t_app *self)
{

}

int	set_game_wall(int fd, t_app *self)
{

}

int	set_game_color(int fd, t_app *self)
{

}

// ASSUMES already validated
int	set_game_elements(int fd, t_app *self)
{
	// if files were huge this would be innefficient because of gnl walking
	// through file multiple times
	// might still be with small file, TODO: check
	// set_game_colors(fd, self);
	// set_game_walls(fd, self);
	// set_game_map(fd, self);

	int		status;
	char	*line;

	status = 1;
	line = NULL;
	while (status > 0)
	{
		status = get_next_line(fd, &line);

		// for test
		if (line)
			printf("%s\n", line);

		if (is_valid_game_color(line, self))
			set_game_color(line, self);
		else if (is_valid_game_wall(line, self))
			set_game_wall(line, self);
		else if (can_set_maplines(self) && is_valid_game_mapline(line, self))
			set_game_mapline(line, self);

		if (line)
			free(line);
	}
	if (status < 0)
		return (EXIT_FAILURE);
	return (status);
}

void	game_init(t_app *self, char* cubfile)
{
	t_walls	*walls;

	self->img = NULL;
	self->mlx_window = NULL;
	self->mlx = NULL;
	self->color_floor = -1;
	self->color_ceiling = -1;
	self->walls = (t_walls *)malloc(sizeof(t_walls));
	if ()

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
