/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:24:35 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/29 18:10:27 by lsarraci         ###   ########.fr       */
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
	fprintf(stderr, "handle_key_press: keycode=%d\n", keycode);
	if (!game)
		return (0);
	if (keycode == 65307)
		close_window(game);
	if (keycode == KEY_LEFT)
		game->input.left = 1;
	else if (keycode == KEY_RIGHT)
		game->input.right = 1;
	else if (keycode == KEY_UP)
		game->input.up = 1;
	else if (keycode == KEY_DOWN)
		game->input.down = 1;
	else if (keycode == KEY_W)
		game->input.w = 1;
	else if (keycode == KEY_A)
		game->input.a = 1;
	else if (keycode == KEY_S)
		game->input.s = 1;
	else if (keycode == KEY_D)
		game->input.d = 1;
	return (0);
}

int	handle_key_release(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return (0);
	if (keycode == KEY_LEFT)
		game->input.left = 0;
	else if (keycode == KEY_RIGHT)
		game->input.right = 0;
	else if (keycode == KEY_UP)
		game->input.up = 0;
	else if (keycode == KEY_DOWN)
		game->input.down = 0;
	else if (keycode == KEY_W)
		game->input.w = 0;
	else if (keycode == KEY_A)
		game->input.a = 0;
	else if (keycode == KEY_S)
		game->input.s = 0;
	else if (keycode == KEY_D)
		game->input.d = 0;
	return (0);
}

void	setup_hooks(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_hook(game->window->win_ptr, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->window->win_ptr, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->window->win_ptr, 17, 0, handle_close, game);
	mlx_loop_hook(game->window->mlx_ptr, render, game);
}
