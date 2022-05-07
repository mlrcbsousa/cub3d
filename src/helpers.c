/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:34:01 by msousa            #+#    #+#             */
/*   Updated: 2022/05/04 15:20:34 by josantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	file_open(char *filename, t_app *self, int (*file_read)(int, t_app*))
{
	int	fd;
	int	status;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_errno(filename);
		return (EXIT_FAILURE);
	}
	status = file_read(fd, self);
	if (close(fd))
	{
		print_errno(filename);
		return (EXIT_FAILURE);
	}
	if (status < 0)
		return (EXIT_FAILURE);
	return (status);
}
