/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:08:22 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/07 17:38:45 by lsarraci         ###   ########.fr       */
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

static void	remove_buffer_data_without_map(t_game *game)
{
	if (game->minimap)
		destroy_minimap(game->minimap);
	if (game->player)
		destroy_player(game->player);
	if (game->z_buffer)
		free(game->z_buffer);
}

static void	remove_buffer_data(t_game *game)
{
	if (game->map)
		free(game->map);
}

static void	remove_window_and_display(t_game *game)
{
	if (game->window)
	{
		remove_buffer_data_without_map(game);
		remove_all_textures(game);
		if (game->window->img_ptr)
			free_pixel_data(game->window->img_ptr,
				game->window->mlx_ptr);
		if (game->window->win_ptr && game->window->mlx_ptr)
		{
			mlx_destroy_window(game->window->mlx_ptr,
				game->window->win_ptr);
			game->window->win_ptr = NULL;
		}
		if (game->window->mlx_ptr)
		{
			mlx_destroy_display(game->window->mlx_ptr);
			free(game->window->mlx_ptr);
			game->window->mlx_ptr = NULL;
		}
		free(game->window);
		game->window = NULL;
	}
}

void	free_game(t_game *game)
{
	if (game)
	{
		remove_window_and_display(game);
		if (game->map)
		{
			free_map(game->map);
			game->map = NULL;
		}
		remove_buffer_data(game);
		free(game);
	}
}
