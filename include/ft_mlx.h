/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:08:07 by msousa            #+#    #+#             */
/*   Updated: 2022/05/09 16:55:03 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_H
# define FT_MLX_H

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

# define SCROLL_UP 4
# define SCROLL_DOWN 5

/* Keys */
# ifdef OS_MAC
#  define KEY_UP 	126
#  define KEY_DOWN 	125
#  define KEY_LEFT 	123
#  define KEY_RIGHT 124
#  define KEY_W 	13
#  define KEY_A 	0
#  define KEY_S 	1
#  define KEY_D 	2
#  define KEY_SPACE 49
#  define KEY_ENTER 36
#  define KEY_ESC 	53
# else
#  define KEY_UP	65362
#  define KEY_DOWN	65364
#  define KEY_LEFT	65361
#  define KEY_RIGHT	65363
#  define KEY_ESC	65307
# endif

# include <mlx.h>

struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

typedef struct s_image	t_image;

#endif
