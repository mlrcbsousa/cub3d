/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:19:36 by msousa            #+#    #+#             */
/*   Updated: 2022/05/08 15:27:16 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_element	*elements_new(char type)
{
	t_element	*elements;

	elements = (t_element *)malloc(sizeof(t_element));
	if (!elements)
		return (NULL);
	elements->type = type;
	elements->next = NULL;
	return (elements);
}

t_element	*elements_last(t_element *elements)
{
	while (elements->next)
		elements = elements->next;
	return (elements);
}

void	elements_addback(t_element **elements, t_element *new)
{
	if (*elements)
	{
		// while (elements->next)
		// 	elements = elements->next;
		// elements->next
		elements_last(*elements)->next = new;
	}
	else
		*elements = new;
}

void	elements_convert_tab(t_element **elements)
{
	int	i;

	i = 0;
	while (i++ < 4)
		elements_addback(elements, elements_new(MAP_SPACE));
}

t_element	*elements_create(char *line)
{
	t_element	*elements;

	elements = NULL;
	while (*line)
	{
		if (*line == MAP_TAB)
			elements_convert_tab(&elements);
		else
			elements_addback(&elements, elements_new(*line));
		line++;
	}
	return (elements);
}

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
