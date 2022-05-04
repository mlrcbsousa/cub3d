/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:16:34 by msousa            #+#    #+#             */
/*   Updated: 2022/05/04 17:42:28 by josantos         ###   ########.fr       */
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
# define SPACE ' '
# define COMMA ','
# define ELEMENTS_MAP " \t01NSWE"
# define ELEMENT_NORTH "NO"
# define ELEMENT_SOUTH "SO"
# define ELEMENT_EAST "EA"
# define ELEMENT_WEST "WE"
# define ELEMENT_FLOOR "F"
# define ELEMENT_CEILING "C"

/* Enums */
enum e_map {
	MAP_NORTH = 'N',
	MAP_SOUTH = 'S',
	MAP_EAST = 'E',
	MAP_WEST = 'W',
	MAP_WALL = '1',
	MAP_SPACE = ' ',
	MAP_TAB = '\t',
	MAP_FLOOR = '0',
};

/* Structs & Types */
typedef struct s_validation	t_validation;
typedef struct s_app		t_app;
typedef struct s_parser		t_parser;
typedef struct s_line		t_line;
typedef struct s_element	t_element;
typedef struct s_settings	t_settings;

struct	s_validation
{
	t_bool north_wall;
	t_bool south_wall;
	t_bool east_wall;
	t_bool west_wall;
	t_bool ceiling;
	t_bool floor;
	t_bool all_valid;
};

struct	s_app
{
	t_image		*img;
	void		*mlx_window;
	void		*mlx;
	t_parser	*parser;
	t_settings	*settings;
};

// Following the single responsibility principle SRP
// struct for parse part of program, once passed turned into t_settings in t_app
struct s_parser
{
	char	*wall_north;
	char	*wall_south;
	char	*wall_east;
	char	*wall_west;
	int		color_floor;
	int		color_ceiling;
	t_line 	*maplines;
};

struct s_element
{
	char		type;
	t_element	*next;
};

struct s_line
{
	t_element	*head;
	int 		n_elements;
	t_line		*next;
};

struct s_settings
{
	t_image	*wall_north;
	t_image	*wall_south;
	t_image	*wall_east;
	t_image	*wall_west;
	int		color_floor;
	int		color_ceiling;
	int		game_width;
	int		game_height;
	char 	**map;
};

/* Functions */

// TODO: move to libft.h
t_bool	ft_isfile_ext(char *filename, char *extension);
t_bool	ft_isfile(char *filename);
void	ft_splitfree(char **parts);
// TODO: move to libft.h

/* parse */
void		parse(t_app *self, char *cubfile);
t_parser	*parser_create(void);
void		parse_exit(char *line, t_parser *parser);
void		parser_destroy(t_parser *parser);
t_bool		is_valid_game_element(char *line);
t_bool		is_valid_game_color(char **split_line, t_validation *valid);
t_bool		is_valid_game_wall(char **split_line, t_validation *valid);
t_bool		is_valid_game_mapline(char **split_line);
t_bool		is_valid_game_map(char **map);
void		set_game_mapline(char* line, t_parser *parser);
void		set_game_wall(char* line, t_parser *parser);
void		set_game_color(char* line, t_parser *parser);
void		maplines_destroy(t_line *maplines);

/* game */
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
void	print_parser(t_parser *parser);
void	print_maplines(t_line *maplines);

#endif
