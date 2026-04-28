/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:42:33 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/28 16:46:04 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	calculate_minimap_offset(t_minimap *minimap, t_game *game)
{
	float	center_x;
	float	center_y;
	float	player_screen_x;
	float	player_screen_y;
	float	player_size;

	center_x = minimap->dim.width / 2.0f;
	center_y = minimap->dim.height / 2.0f;
	player_size = minimap->scale / 2.0f;
	player_screen_x = (game->player->pos.x * minimap->scale)
		+ (player_size / 2.0f);
	player_screen_y = (game->player->pos.y * minimap->scale)
		+ (player_size / 2.0f);
	minimap->offset.x = (int)(center_x - player_screen_x);
	minimap->offset.y = (int)(center_y - player_screen_y);
}
