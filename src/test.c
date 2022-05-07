/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:48:22 by msousa            #+#    #+#             */
/*   Updated: 2022/05/08 00:39:06 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_parser(t_parser *parser)
{
	if (!parser)
		return ;
	printf("\n--Parser--\n");
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

void	print_elements(t_element *elements)
{
	if (!elements)
		return ;
	while (elements)
	{
		printf("%c, ", elements->type);
		elements = elements->next;
	}
	printf("\n");
}

void	print_maplines(t_line *maplines)
{
	if (!maplines)
		return ;
	while (maplines)
	{
		print_elements(maplines->head);
		maplines = maplines->next;
	}
	printf("========================================= MAPLINES END\n\n");
}
