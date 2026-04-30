/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:19:29 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/30 17:12:03 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"
#include <stdio.h>

static int	update_input_render(t_game *game)
{
	if (game->input.left)
		handle_arrow_press(KEY_LEFT, game->player, game);
	if (game->input.right)
		handle_arrow_press(KEY_RIGHT, game->player, game);
	if (game->input.w)
		set_directional_movement(KEY_W, game->player, game);
	if (game->input.s)
		set_directional_movement(KEY_S, game->player, game);
	if (game->input.a)
		set_directional_movement(KEY_A, game->player, game);
	if (game->input.d)
		set_directional_movement(KEY_D, game->player, game);
	return (0);
}

int	render(void *param)
{
	t_game		*game;
	t_data		*data;
	static int	frame = 0;

	game = (t_game *)param;
	update_timer(&game->timer);
	if (!game || !game->window || !game->window->img_ptr)
		return (0);
	data = game->window->img_ptr;
	update_input_render(game);
	clear_buffer(data, 0x000000);
	render_background(data, game);
	if (game->minimap)
	{
		render_minimap(game->minimap, game, 0);
		composite_minimap_to_main(data, game->minimap);
	}
	render_frame(data, game->window->mlx_ptr, game->window->win_ptr);
	frame++;
	return (0);
}
