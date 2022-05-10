/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:29:05 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 01:11:06 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include "ft_point.h"

struct	s_vector
{
	double	angle;
	double	size;
};

typedef struct s_vector	t_vector;

double		trim(double a);
t_vector	vector(double angle, double size);
t_point		point_move(t_point p, t_vector v);

#endif
