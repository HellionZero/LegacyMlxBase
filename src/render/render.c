/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:19:29 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/29 19:44:47 by lsarraci         ###   ########.fr       */
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
	draw_rectangle(data, (t_icoord){100, 100}, (t_dim){200, 150}, 0xFF0000);
	fprintf(stderr, "render: skipping draw_line/draw_polygon\n");
	fprintf(stderr, "render: about to render minimap\n");
	if (game->minimap)
	{
		fprintf(stderr, "render: calling render_minimap\n");
		render_minimap(game->minimap, game, 0);
		fprintf(stderr, "render: calling composite_minimap_to_main\n");
		composite_minimap_to_main(data, game->minimap);
	}
	render_frame(data, game->window->mlx_ptr, game->window->win_ptr);
	frame++;
	return (0);
}
