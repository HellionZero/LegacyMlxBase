/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_engine.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:56:15 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/29 20:28:40 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_ENGINE_H
# define CUB_ENGINE_H

# include "cub_structs.h"

int		is_position_walkable(t_map *map, float x, float y);
void	move_player(t_player *player, t_map *map, float move_step);
void	strafe_player(t_player *player, t_map *map, float move_step);
void	set_directional_movement(int keycode, t_player *player, t_game *game);
void	set_player_ray(t_game *game, t_player *player, t_ray *ray,
			float ray_angle);
void	render_first_ray(t_player *player, t_minimap *map, t_ray *ray);
int		rect_collides(t_map *map, t_dcoord pos, float radius);
void	player_to_frect(t_dcoord pos, float radius, t_frect *out);
void	frect_sample_point(const t_frect *r, int i, int j,
			t_dcoord *out);
int		frect_collides_map(t_map *map, const t_frect *r, int i);

#endif