/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 00:57:45 by msousa            #+#    #+#             */
/*   Updated: 2022/05/08 02:26:51 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_settings	*settings_create(void)
{
	t_settings	*settings;

	settings = (t_settings *)malloc(sizeof(t_settings));
	if (!settings)
		return (NULL);
	settings->color_floor = -1;
	settings->color_ceiling = -1;
	settings->wall_north = NULL;
	settings->wall_south = NULL;
	settings->wall_east = NULL;
	settings->wall_west = NULL;
	settings->player = NULL;
	settings->map = NULL;
	settings->width = -1;
	settings->height = -1;
	return (settings);
}

void	settings_destroy(t_settings *settings)
{
	if (!settings)
		return ;
	free(settings);
}
