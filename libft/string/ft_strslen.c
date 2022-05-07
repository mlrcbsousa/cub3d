/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:36:09 by msousa            #+#    #+#             */
/*   Updated: 2022/05/07 16:51:19 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Let segfault when str is NULL so we know not to call funciton on NULL
size_t	ft_strslen(char **strs)
{
	size_t	length;

	length = 0;
	while (*strs++)
		length++;
	return (length);
}
