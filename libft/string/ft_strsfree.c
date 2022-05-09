/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:41:11 by msousa            #+#    #+#             */
/*   Updated: 2022/05/07 19:43:46 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strsfree(char **strs)
{
	char	**tmp;

	if (!strs)
		return ;
	tmp = strs;
	while (*strs)
		free(*strs++);
	free(tmp);
}
