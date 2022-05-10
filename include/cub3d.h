/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:16:34 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 01:10:19 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# include "libft.h"
# include "ft_mlx.h"
# include "ft_point.h"
# include "ft_vector.h"

/* Constants */
# define SPACE ' '
# define COMMA ','
# define ELEMENTS_MAP " \t01NSWE"
# define ELEMENTS_PLAYER "NSEW"
# define ELEMENT_NORTH "NO"
# define ELEMENT_SOUTH "SO"
# define ELEMENT_EAST "EA"
# define ELEMENT_WEST "WE"
# define ELEMENT_FLOOR "F"
# define ELEMENT_CEILING "C"

# define WIDTH	1200
# define WIDTH2	600
# define HEIGHT 800
# define HEIGHT2 400
# define SIZE 64
# define BITS 6 // x 64 same as << BITS, / 64 same as >> BITS
# define MOVE 5
# define PI 3.14159265359
# define DR 0.00087266666
# define BIG_LENGTH 1000000

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
typedef struct s_app		t_app;
typedef struct s_parser		t_parser;
typedef struct s_line		t_line;
typedef struct s_element	t_element;
typedef struct s_settings	t_settings;
typedef struct s_player		t_player;

struct	s_app
{
	t_image		*img;
	void		*mlx_window;
	void		*mlx;
	t_parser	*parser;
	t_settings	*settings;
	t_player	*player;
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
	char 	**parts;
	char 	*line;
	t_bool 	has_player;
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
	int		width;
	int		height;
	char 	**map;
};

struct s_player
{
	double		angle;
	t_point		p;
};

/* Functions */

// TODO: move to libft.h
t_bool	is_empty_line(char *line);
t_bool	is_valid_rgb(char **colors);
int g_wall_color;
// TODO: move to libft.h

/* parse */
void		parse(t_app *self, char *cubfile);
t_parser	*parser_create(void);
void    	parse_exit(t_parser *parser, char *error);
void		parser_destroy(t_parser *parser);
t_bool		could_be_game_color(char *line);
t_bool		could_be_game_wall(char *line);
t_bool		could_be_game_mapline(char *line);

// t_bool		is_valid_game_map(char **map);
void		set_game_mapline(char* line, t_parser *parser);
void		set_game_wall(char* line, t_parser *parser);
void		set_game_color(char* line, t_parser *parser);

/* elements */
t_element	*elements_new(char type);
void		elements_addback(t_element **elements, t_element *new);
void		elements_convert_tab(t_element **elements);
t_element	*elements_create(char *line);
int			elements_size(t_element *elements);

/* maplines */
t_line	*mapline_create(char *line);
void	maplines_destroy(t_line **maplines);
t_line	*mapline_last(t_line *mapline);
void	mapline_addback(t_parser *parser, t_line *mapline);
int		maplines_size(t_line *mapline);

/* settings */
void		settings_init(t_app *self);
t_settings	*settings_create(void);
void		settings_destroy(t_settings *settings);

/* map */
void		map_create(t_line *maplines, t_settings *settings);
t_bool		is_map_closed(t_settings *settings);
void		map_loop(t_app *self, t_bool (*f)(t_app *, int, int));

/* player */
void		player_init(t_app *self);
t_player	*player_create(void);
t_bool		set_player(t_app *self, int i, int j);

/* mlx */
void	draw(t_app *self);
void	raycast(t_app *self);
void	draw_line(t_app *self, int ray, double length);
int		key_hook(int key, t_app *self);
void	move(int key, t_app *self);
int		close_app(t_app *self);

/* angle */
double	trim(double a);

/* color */
int		create_trgb(int t, int r, int g, int b);

/* helpers */
void    print_errno(char* input);
void    print_error(char* input, char *msg);
int		file_open(char *filename, t_app *self, int (*file_read)(int, t_app*));

/* test */
void	print_parser(t_parser *parser);
void	print_maplines(t_line *maplines);
void	print_map(t_settings *settings);
void	print_player(t_player *player);

#endif
