/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:19:29 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/20 18:34:33 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	render(void *param)
{
	t_game	*game;
	t_data	*data;

	game = (t_game *)param;
	update_timer(&game->timer);
	if (!game || !game->window || !game->window->img_ptr)
		return (0);
	data = game->window->img_ptr;
	clear_buffer(data, 0x000000);
	if (game->wall_texture)
		draw_textured_rectangle(data, (t_icoord){600, 450},
			(t_dim){150, 150}, game->wall_texture);
	draw_rectangle(data, (t_icoord){100, 100}, (t_dim){200, 150}, 0xFF0000);
	draw_line(data, (t_icoord){0, 0}, (t_icoord){400, 300}, 0x00FF00);
	draw_line(data, (t_icoord){400, 0}, (t_icoord){0, 300}, 0x0000FF);
	draw_polygon(data, (t_icoord[]){(t_icoord){100, 100},
		(t_icoord){300, 100}, (t_icoord){200, 250}}, 3, 0xFFFF00);
	render_temporary_map(game);
	render_frame(data, game->window->mlx_ptr, game->window->win_ptr);
	return (0);
}
