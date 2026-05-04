/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_layer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 14:40:23 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/30 15:30:42 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	render_background(t_data *data, t_game *game)
{
	if (!data || !game)
		return ;
	clear_buffer(data, 0x000000);
	if (game->map)
	{
		draw_rectangle(data, (t_icoord){0, 0},
			(t_dim){WINDOW_WIDTH, WINDOW_HEIGHT},
			game->map->ceiling_color);
		draw_rectangle(data, (t_icoord){0, WINDOW_HEIGHT / 2},
			(t_dim){WINDOW_WIDTH, WINDOW_HEIGHT / 2},
			game->map->floor_color);
	}
}
