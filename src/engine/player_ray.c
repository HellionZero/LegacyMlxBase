/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:14:07 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/28 18:23:39 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	set_player_ray(t_game *game, t_player *player, t_ray *ray,
			float ray_angle)
{
	ray->dir.x = cos(ray_angle);
	ray->dir.y = sin(ray_angle);
	ray->pos.x = player->pos.x;
	ray->pos.y = player->pos.y;
	ray->length = 0.0f;
	ray->hit_wall = 0;
	ray->hit_sprite = 0;
	draw_line(game->minimap->buffer, (t_icoord){(int)player->pos.x,
		(int)player->pos.y},
		(t_icoord){(int)(player->pos.x + ray->dir.x * 5),
		(int)(player->pos.y + ray->dir.y * 5)}, RED);
}
