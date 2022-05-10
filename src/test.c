/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:48:22 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 15:04:20 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_parser(t_parser *parser)
{
	if (!parser)
		return ;
	printf("\n--PARSER--\n");
	if (parser->wall_north)
		printf("wall_north: %s\n", parser->wall_north);
	if (parser->wall_south)
		printf("wall_south: %s\n", parser->wall_south);
	if (parser->wall_east)
		printf("wall_east: %s\n", parser->wall_east);
	if (parser->wall_west)
		printf("wall_west: %s\n", parser->wall_west);
	printf("color_floor: %d\n", parser->color_floor);
	printf("color_ceiling: %d\n", parser->color_ceiling);
	if (parser->maplines)
		print_maplines(parser->maplines);
}

void	print_player(t_player *player)
{
	if (!player)
		return ;
	printf("\n--PLAYER--\n");
	printf("x: %f\n", player->p.x);
	printf("y: %f\n", player->p.y);
	printf("a: %f\n", player->angle);
}

void	print_elements(t_element *elements)
{
	if (!elements)
		return ;
	while (elements)
	{
		printf("%c, ", elements->type);
		elements = elements->next;
	}
}

void	print_maplines(t_line *mapline)
{
	if (!mapline)
		return ;
	while (mapline)
	{
		print_elements(mapline->head);
		printf("  size: %d\n", mapline->n_elements);
		mapline = mapline->next;
	}
	printf("========================================= PARSER END\n\n");
}

// TODO: use map_loop
void	print_map(t_settings *settings)
{
	int			i;
	int			j;

	if (!settings->map)
		return ;
	j = 0;
	while (j < settings->height)
	{
		i = 0;
		while (i < settings->width)
			printf("%c ", settings->map[i++][j]);
		printf("\n");
		j++;
	}
	printf("========================================= MAP END\n\n");
}
