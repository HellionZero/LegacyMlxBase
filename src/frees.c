/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:08:22 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/05 17:09:03 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	remove_all_textures(t_game *game)
{
	if (game->window && game->window->mlx_ptr && game->map)
	{
		if (game->map->north_texture)
			remove_texture(game->window->mlx_ptr,
				game->map->north_texture);
		if (game->map->south_texture)
			remove_texture(game->window->mlx_ptr,
				game->map->south_texture);
		if (game->map->west_texture)
			remove_texture(game->window->mlx_ptr,
				game->map->west_texture);
		if (game->map->east_texture)
			remove_texture(game->window->mlx_ptr,
				game->map->east_texture);
	}
}
