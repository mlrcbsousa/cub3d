/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:18:53 by josantos          #+#    #+#             */
/*   Updated: 2022/05/10 23:36:46 by josantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

t_bool	invalid(int argc, char *argv[])
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
