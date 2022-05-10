/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:34:01 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 23:21:51 by josantos         ###   ########.fr       */
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

void	print_errno(char *input)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (input)
	{
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	perror("");
}

void	print_error(char *input, char *msg)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (input)
	{
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	usage(void)
{
	ft_putendl_fd(NULL, STDOUT_FILENO);
	ft_putendl_fd("Usage: ./cub3d <map>", STDOUT_FILENO);
	ft_putendl_fd(NULL, STDOUT_FILENO);
	ft_putendl_fd("   - map		Path to *.cub file", STDOUT_FILENO);
	ft_putendl_fd(NULL, STDOUT_FILENO);
	exit(0);
}
