/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maplines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:20:28 by msousa            #+#    #+#             */
/*   Updated: 2022/05/08 15:59:50 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	maplines_size(t_line *mapline)
{
	int	size;

	size = 0;
	while (mapline)
	{
		mapline = mapline->next;
		size++;
	}
	return (size);
}


// void	ft_lstdelone(t_list *lst, void (*del)(void *))
// {
// 	if (lst && del)
// 	{
// 		del(lst->content);
// 		free(lst);
// 	}
// }

// void	ft_lstclear(t_list **lst, void (*del)(void *))
// {
// 	t_list	*tmp;

// 	while (*lst)
// 	{
// 		tmp = *lst;
// 		*lst = (*lst)->next;
// 		ft_lstdelone(tmp, del);
// 	}
// }

void	maplines_destroy(t_line *maplines)
{
	// TODO: linked list of linked lists destroy
	(void)maplines;
}

t_line	*mapline_create(char *line)
{
	t_line	*mapline;

	mapline = (t_line *)malloc(sizeof(t_line));
	if (!mapline)
		return (NULL);
	mapline->head = elements_create(line);
	mapline->n_elements = elements_size(mapline->head);
	mapline->next = NULL;
	return (mapline);
}

t_line	*mapline_last(t_line *mapline)
{
	while (mapline->next)
		mapline = mapline->next;
	return (mapline);
}

void	mapline_addback(t_parser *parser, t_line *mapline)
{
	if (parser->maplines)
		mapline_last(parser->maplines)->next = mapline;
	else
		parser->maplines = mapline;
}
