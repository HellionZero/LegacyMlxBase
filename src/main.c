/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:08:39 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/05 17:17:15 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	remove_buffer_data_without_map(t_game *game)
{
	if (game->minimap)
		destroy_minimap(game->minimap);
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

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3D <path_to_map.cub>\n", 2);
		return (1);
	}
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		ft_putstr_fd("Failed to allocate memory for game\n", 2);
		return (1);
	}
	init_game(game, argv);
	setup_hooks(game);
	mlx_loop(game->window->mlx_ptr);
	return (0);
}
