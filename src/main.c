/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:08:39 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/29 14:45:01 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	remove_all_textures(t_game *game)
{
	if (game->window && game->window->mlx_ptr)
	{
		if (game->wall_texture)
			remove_texture(game->window->mlx_ptr, game->wall_texture);
		if (game->floor_texture)
			remove_texture(game->window->mlx_ptr, game->floor_texture);
		if (game->ceiling_texture)
			remove_texture(game->window->mlx_ptr, game->ceiling_texture);
	}
}

static void	remove_buffer_data(t_game *game)
{
	if (game->minimap)
		destroy_minimap(game->minimap);
	if (game->player)
		destroy_player(game->player);
	if (game->map)
		free(game->map);
}

void	free_game(t_game *game)
{
	if (game)
	{
		remove_buffer_data(game);
		if (game->window)
		{
			remove_all_textures(game);
			if (game->window->img_ptr)
				free_pixel_data(game->window->img_ptr,
					game->window->mlx_ptr);
			if (game->window->win_ptr)
				mlx_destroy_window(game->window->mlx_ptr,
					game->window->win_ptr);
			if (game->window->mlx_ptr)
			{
				mlx_destroy_display(game->window->mlx_ptr);
				free(game->window->mlx_ptr);
			}
			free(game->window);
		}
		free(game);
	}
}

int	main(void)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		ft_putstr_fd("Failed to allocate memory for game\n", 2);
		return (1);
	}
	init_game(game);
	init_timer(&game->timer);
	setup_hooks(game);
	mlx_loop(game->window->mlx_ptr);
	free_game(game);
	return (0);
}
