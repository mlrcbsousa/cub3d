/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:16:34 by msousa            #+#    #+#             */
/*   Updated: 2022/05/02 19:22:28 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "ft_mlx.h"
# include "ft_point.h"

/* Constants */
# define WIDTH	1200
# define HEIGHT 800

/* Enums */

/* Structs & Types */
typedef struct s_app	t_app;
typedef struct s_walls	t_walls;

struct	s_app
{
	t_image		*img;
	void		*mlx_window;
	void		*mlx;
	int			color_floor;
	int			color_ceiling;
	t_walls		*walls;
};

struct s_walls
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
};

/* Functions */

// TODO: move to libft.h
t_bool	ft_isfile_ext(char *filename, char *extension);
t_bool	ft_isfile(char *filename);
// TODO: move to libft.h

/* game */
void	game_init(t_app *self, char* cubfile);
void	game_loop(t_app *self);
void	game_destroy(t_app *self);

/* mlx */
void	draw(t_app *self);
void	set_hooks(t_app *self);

/* color */
int		create_trgb(int t, int r, int g, int b);

/* helpers */
void    print_errno(char* input);
void    print_error(char* input, char *msg);
int		file_open(char *filename, t_app *self, int (*file_read)(int, t_app*));

/* test */


#endif
