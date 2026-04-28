/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:34:14 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/28 16:34:42 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

t_player	*create_player(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos = (t_icoord){2, 2};
	player->dim = (t_dim){1, 1};
	player->color = GREEN;
	return (player);
}

void	destroy_player(t_player *player)
{
	free(player);
}
