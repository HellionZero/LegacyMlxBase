/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:34:14 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/29 20:04:14 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

t_player	*create_player(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos = (t_dcoord){1.5, 1.5};
	player->dim = (t_dim){1, 1};
	player->color = GREEN;
	player->angle = 0.0f;
	player->collision_radius = 0.3f;
	return (player);
}

void	destroy_player(t_player *player)
{
	free(player);
}
