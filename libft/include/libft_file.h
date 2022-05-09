/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_file.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:09:51 by msousa            #+#    #+#             */
/*   Updated: 2022/05/07 15:47:38 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FILE_H
# define LIBFT_FILE_H

# include <fcntl.h>

# include "libft.h"

t_bool	ft_isfile_ext(char *filename, char *extension);
t_bool	ft_isfile(char *filename);

#endif
