/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_streq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:51:42 by msousa            #+#    #+#             */
/*   Updated: 2022/05/04 15:33:21 by josantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_streq(char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return false
	return (s1 && s2 && ft_ternary(ft_strcmp(s1, s2), FALSE, TRUE));
}

/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc == 3)
		printf("%s == %s : %d\n", argv[1], argv[2], ft_streq(argv[1], argv[2]));
	else
		printf("Error: requires 2 string args.\n");
	return (0);
}
*/
