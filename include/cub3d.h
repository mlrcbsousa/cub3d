/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:16:34 by msousa            #+#    #+#             */
/*   Updated: 2022/05/01 17:53:19 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "ft_mlx.h"
# include "ft_point.h"

/* Constants */
# define WIDTH 320
# define HEIGHT 200

/* Enums */

/* Structs & Types */
typedef struct s_app	t_app;

struct	s_app
{
	t_image		*img;
	void		*mlx_window;
	void		*mlx;
};

/* Functions */

/* mlx */
void	draw(t_app *self);
void	set_hooks(t_app *self);

/* helpers */
void    print_errno(char* input);
void    print_error(char* input, char *msg);

/* test */


#endif
