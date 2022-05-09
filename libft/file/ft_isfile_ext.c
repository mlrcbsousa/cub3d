/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfile_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:44:36 by msousa            #+#    #+#             */
/*   Updated: 2022/05/07 15:48:55 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// use WITH dot
t_bool	ft_isfile_ext(char *filename, char *extension)
{
	unsigned int	len_filename;
	unsigned int	len_extension;

	len_filename = ft_strlen(filename);
	len_extension = ft_strlen(extension);
	if (len_filename <= len_extension)
		return (FALSE);
	return (ft_streq(filename + len_filename - len_extension, extension));
}
