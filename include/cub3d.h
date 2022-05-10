/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:16:34 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 21:20:49 by msousa           ###   ########.fr       */
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
# define WALLS 4
# define PI 3.14159265359
# define DR 0.00087266666
# define BIG_LENGTH 1000000

/* Angles in Width Pixel units */
# define WALL_HEIGHT SIZE
# define ANGLE60	WIDTH
# define ANGLE30	600
# define ANGLE15	300
# define ANGLE90 	1800
# define ANGLE180	3600
# define ANGLE270	5400
# define ANGLE360	7200
# define ANGLE0		0
# define ANGLE5		100
# define ANGLE10	200

/* Types */
typedef struct s_app		t_app;
typedef struct s_parser		t_parser;
typedef struct s_line		t_line;
typedef struct s_element	t_element;
typedef struct s_settings	t_settings;
typedef struct s_player		t_player;
typedef struct s_ray		t_ray;
typedef struct s_tables		t_tables;
typedef enum e_wall			t_wall;

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

enum e_wall {
	WALL_NORTH,
	WALL_SOUTH,
	WALL_EAST,
	WALL_WEST,
	WALL_NULL = -1,
};

// TODO: reduce settings and parser structs using enums and arrays
enum e_color {
	COLOR_FLOOR,
	COLOR_CEILING,
	COLOR_NULL = -1,
};

/* Structs */
struct	s_tables
{
	double	sin[ANGLE360 + 1];
	double	sin_i[ANGLE360 + 1];
	double	cos[ANGLE360 + 1];
	double	cos_i[ANGLE360 + 1];
	double	tan[ANGLE360 + 1];
	double	tan_i[ANGLE360 + 1];
	double	fish[ANGLE360 + 1];
	double	step_x[ANGLE360 + 1];
	double	step_y[ANGLE360 + 1];
};

struct	s_app
{
	t_image		*img;
	void		*mlx_window;
	void		*mlx;
	t_parser	*parser;
	t_settings	*settings;
	t_player	*player;
	t_tables	tables;
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
	t_image	**walls;
	int		color_floor;
	int		color_ceiling;
	int		width;
	int		height;
	char 	**map;
};

struct s_player
{
	int			angle;
	t_point		p;
};

struct	s_ray
{
	double	length;
	t_point	p;
	t_wall	wall;
	int		angle;
};

/* Functions */

// TODO: move to libft.h
t_bool	is_empty_line(char *line);
t_bool	is_valid_rgb(char **colors);
int g_wall_color;
// TODO: move to libft.h

/* tables */
void	tables_init(t_app *self);

/* parse */
void		parse(t_app *self, char *cubfile);
t_parser	*parser_create(void);
void    	parse_exit(t_app *self, char *error);
void		parser_destroy(t_app *self);
t_bool		could_be_game_color(char *line);
t_bool		could_be_game_wall(char *line);
t_bool		could_be_game_mapline(char *line);
void		set_game_mapline(char* line, t_app *self);
void		set_game_wall(char* line, t_app *self);
void		set_game_color(char* line, t_app *self);

/* elements */
t_element	*elements_new(char type);
void		elements_addback(t_element **elements, t_element *new);
void		elements_convert_tab(t_element **elements);
t_element	*elements_create(char *line);
int			elements_size(t_element *elements);
t_bool		is_element_bounded_and_wall(t_settings *s, t_point p);
t_bool		is_element_bounded_and_not_wall(t_settings *s, t_point p);

/* maplines */
t_line		*mapline_create(char *line);
void		maplines_destroy(t_line **maplines);
t_line		*mapline_last(t_line *mapline);
void		mapline_addback(t_parser *parser, t_line *mapline);
int			maplines_size(t_line *mapline);

/* settings */
void		settings_init(t_app *self);
t_settings	*settings_create(void);
void		settings_destroy(t_settings *settings);
void		settings_exit(t_settings *settings, char *error);

/* map */
void		map_create(t_line *maplines, t_settings *settings);
void		map_destroy(t_settings *s);
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
double	arc_to_rad(double arc_angle);

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
