/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_engine.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:56:15 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/30 17:10:06 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_ENGINE_H
# define CUB_ENGINE_H

# include "cub_structs.h"

float 	*init_zbuffer(t_game *game);

int		is_position_walkable(t_map *map, float x, float y);
void	move_player(t_player *player, t_map *map, float move_step);
void	strafe_player(t_player *player, t_map *map, float move_step);
void	set_directional_movement(int keycode, t_player *player, t_game *game);
void	render_first_ray(t_player *player, t_minimap *map, t_ray *ray);
int		rect_collides(t_map *map, t_dcoord pos, float radius);
void	player_to_frect(t_dcoord pos, float radius, t_frect *out);
void	frect_sample_point(const t_frect *r, int i, int j,
			t_dcoord *out);
int		frect_collides_map(t_map *map, const t_frect *r, int i);
void	trace_ray(t_ray *ray, t_minimap *map, t_dcoord *hit_point);
void	draw_ray_on_minimap(t_ray *ray, t_minimap *map, t_player *player,
			t_dcoord *hit_point);
void	draw_fov_rays(t_player *player, t_minimap *map, t_data *target);

void	init_camera(t_camera *camera, t_player *player);
void	rotate_camera(t_camera *camera, float angle);
void	move_camera(t_camera *camera, t_map *map, float move_step);
void	get_camera_ray(t_camera *camera, int x, t_ray *ray);
void 	update_camera(t_camera *camera, t_player *player);

//void	cast_ray(t_game *game, t_data *data);

#endif