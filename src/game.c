/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 18:38:35 by msousa            #+#    #+#             */
/*   Updated: 2022/05/04 16:07:36 by josantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	valid_game_element(char *line)
{
	char			**split_line;
	t_validation	*valid;
	
	valid = init_validation();
	split_line = ft_split(line, " ");
	if (ft_strcmp(split_line[0], "NO") || ft_strcmp(split_line[0], "WE") ||
		ft_strcmp(split_line[0], "SO") || ft_strcmp(split_line[0], "EA"))
		return (is_valid_game_wall(split_line, valid));
	else if (ft_strcmp(split_line[0], "F") ||
		ft_strcmp(split_line[0], "C"))
		return (is_validate_game_color(split_line, valid));
	check_validation(valid);
	if (valid-> all_valid == TRUE)
		return(is_valid_game_mapline(split_line, line));
	return (FALSE);
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
