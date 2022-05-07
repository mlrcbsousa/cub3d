// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   validation.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: josantos <josantos@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/05/04 14:46:17 by josantos          #+#    #+#             */
// /*   Updated: 2022/05/04 17:10:59 by josantos         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3d.h"

// t_bool	*init_validation(void)
// {
// 	t_validation	*valid;

// 	valid->north_wall = FALSE;
// 	valid->south_wall = FALSE;
// 	valid->east_wall = FALSE;
// 	valid->west_wall = FALSE;
// 	valid->ceiling = FALSE;
// 	valid->floor = FALSE;
// 	valid->all_valid = FALSE;
// }

// void	check_validation(t_validation *valid)
// {
// 	if (valid->north_wall && valid->south_wall && valid->east_wall &&
// 		valid->west_wall && valid->ceiling && valid->floor)
// 		valid->all_valid = TRUE;
// }

// void	validate_element(char *element_type, t_validation *valid)
// {
// 	if (ft_strcmp(element_type, "NO"))
// 		valid->north_wall = TRUE;
// 	else if (ft_strcmp(element_type, "SO"))
// 		valid->south_wall = TRUE;
// 	else if (ft_strcmp(element_type, "WE"))
// 		valid->west_wall = TRUE;
// 	else if (ft_strcmp(element_type, "EA"))
// 		valid->east_wall = TRUE;
// 	else if (ft_strcmp(element_type, "F"))
// 		valid->floor = TRUE;
// 	else if (ft_strcmp(element_type, "C"))
// 		valid->ceiling = TRUE;
// }
