/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:34:14 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/09 19:13:13 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

float	set_start_angle(char orientation)
{
	float	angle;

	angle = 0;
	if (orientation == 'N')
		angle = 3 * PI / 2;
	else if (orientation == 'S')
		angle = PI / 2;
	else if (orientation == 'E')
		angle = 0;
	else if (orientation == 'W')
		angle = PI;
	return (angle);
}

t_player	*create_player(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos = (t_dcoord){1.5, 1.5};
	player->dim = (t_dim){1, 1};
	player->color = GREEN;
	player->orientation = 'N';
	player->angle = set_start_angle(player->orientation);
	player->collision_radius = 0.3f;
	return (player);
}

void	destroy_player(t_player *player)
{
	free(player);
}
