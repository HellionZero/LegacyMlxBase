/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:24:35 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/20 14:44:01 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_game(game);
	exit(0);
}

int	handle_close(void *param)
{
	close_window(param);
	return (0);
}

int	handle_key_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == 65307)
		close_window(game);
	return (0);
}

void	setup_hooks(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_hook(game->window->win_ptr, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->window->win_ptr, 17, 0, handle_close, game);
	mlx_loop_hook(game->window->mlx_ptr, render, game);
}
