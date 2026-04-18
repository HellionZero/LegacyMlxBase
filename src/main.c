/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:08:39 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/18 18:14:22 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	free_game(t_game *game)
{
	if (game)
	{
		if (game->window)
		{
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

	game = malloc(sizeof(t_game));
	if (!game)
	{
		ft_putstr_fd("Failed to allocate memory for game\n", 2);
		return (1);
	}
	game->window = create_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!game->window)
	{
		free_game(game);
		return (1);
	}
	setup_hooks(game);
	mlx_loop(game->window->mlx_ptr);
	free_game(game);
	return (0);
}
