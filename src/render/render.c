/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbara.drummond <barbara.drummond@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:19:29 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/09 23:26:51 by barbara.dru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"
#include <stdio.h>

static int	update_input_render(t_game *game)
{
	if (game->input.left)
		handle_arrow_press(KEY_LEFT, game->map->player, game);
	if (game->input.right)
		handle_arrow_press(KEY_RIGHT, game->map->player, game);
	if (game->input.w)
		set_directional_movement(KEY_W, game->map->player, game);
	if (game->input.s)
		set_directional_movement(KEY_S, game->map->player, game);
	if (game->input.a)
		set_directional_movement(KEY_A, game->map->player, game);
	if (game->input.d)
		set_directional_movement(KEY_D, game->map->player, game);
	return (0);
}

int	render(void *param)
{
	t_game		*game;
	t_data		*data;

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
		render_minimap(game->minimap, game);
		cast_ray(game, data);
		composite_minimap_to_main(data, game->minimap);
	}
	else
		cast_ray(game, data);
	render_frame(data, game->window->mlx_ptr, game->window->win_ptr);
	return (0);
}
