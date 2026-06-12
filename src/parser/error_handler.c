/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:36:36 by bmoreira          #+#    #+#             */
/*   Updated: 2026/05/09 19:20:02 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->north_path)
		free(map->north_path);
	if (map->south_path)
		free(map->south_path);
	if (map->west_path)
		free(map->west_path);
	if (map->east_path)
		free(map->east_path);
	if (map->grid)
		ft_free_split(map->grid);
	if (map->player)
		destroy_player(map->player);
	free(map);
}

void	error_handler(t_map *map, char **split, int exit_code)
{
	if (split)
		ft_free_split(split);
	free_map(map);
	if (exit_code == READ_FILE)
		printf("Error reading file.\n");
	else if (exit_code == INVALID_COLOR)
		printf("Invalid color. Please provide a valid RGB value: "
			"[0-255],[0-255],[0-255]\n");
	else if (exit_code == INVALID_ELEMENT)
		printf("Invalid element. Please provide a valid texture path or RGB."
			"It must contain two space separated values: [ID] [PATH/COLOR]\n");
	else if (exit_code == JOIN_CONTENT)
		printf("Error joining content with current buffer.\n");
	else if (exit_code == INVALID_GRID)
		printf("Invalid grid for map provided.\n");
	exit (1);
}
