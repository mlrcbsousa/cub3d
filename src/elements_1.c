/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 00:29:41 by msousa            #+#    #+#             */
/*   Updated: 2022/05/09 00:29:52 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	elements_size(t_element *elements)
{
	int	size;

	size = 0;
	while (elements)
	{
		elements = elements->next;
		size++;
	}
	return (size);
}
