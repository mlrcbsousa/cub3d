/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:20:24 by josantos          #+#    #+#             */
/*   Updated: 2022/05/04 15:21:01 by josantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    print_errno(char* input)
{
    ft_putstr_fd("Error\n", STDERR_FILENO);
	if (input)
	{
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
    perror("");
}

void    print_error(char* input, char *msg)
{
    ft_putstr_fd("Error\n", STDERR_FILENO);
	if (input)
	{
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
    ft_putendl_fd(msg, STDERR_FILENO);
}