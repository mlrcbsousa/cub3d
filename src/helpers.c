/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:34:01 by msousa            #+#    #+#             */
/*   Updated: 2022/05/01 17:49:09 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    print_errno(char* input)
{
    ft_putstr_fd("cub3d: ", STDERR_FILENO);
	if (input)
	{
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
    perror("");
}

void    print_error(char* input, char *msg)
{
    ft_putstr_fd("cub3d: ", STDERR_FILENO);
	if (input)
	{
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
    ft_putendl_fd(msg, STDERR_FILENO);
}
