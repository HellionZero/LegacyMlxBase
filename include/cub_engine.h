/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_engine.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:56:15 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/04 17:11:46 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_ENGINE_H
# define CUB_ENGINE_H

# include "cub_structs.h"

/* ---------------------directional movement functions ------------------- */

int				is_position_walkable(t_map *map, float x, float y);
void			move_player(t_player *player, t_map *map, float move_step);
void			strafe_player(t_player *player, t_map *map, float move_step);
void			set_directional_movement(int keycode, t_player *player,
					t_game *game);

/* ------------------- collision detection functions ------------------- */

void			player_to_frect(t_dcoord pos, float radius, t_frect *out);
void			frect_sample_point(const t_frect *r, int i, int j,
					t_dcoord *out);
int				frect_collides_map(t_map *map, const t_frect *r, int i);
int				rect_collides(t_map *map, t_dcoord pos, float radius);

/*----------------------- raycasting related functions ------------------ */

void			trace_ray(t_ray *ray, t_minimap *map, t_dcoord *hit_point);
void			draw_ray_on_minimap(t_ray *ray, t_minimap *map,
					t_dcoord *hit_point);
void			render_ray(t_ray *ray, t_minimap *map);
void			render_first_ray(t_player *player, t_minimap *map, t_ray *ray);

void			draw_fov_rays(t_player *player, t_minimap *map, t_data *target);

/* -------------------DDA related functions ------------------- */

void			init_dda_variables(t_ray *ray, t_dcoord *rd, t_icoord *rmap,
					t_dcoord *delta_dist);
void			calc_side_dist(t_dda *dda, t_dcoord ray_pos);
int				check_bounds(t_dda *dda, t_minimap *map);
void			update_ray_hit_data(t_ray *ray, t_dda *dda,
					t_dcoord *hit_point);
void			update_ray_step(t_dda *dda);

/* -------------------ray initialization functions ------------------- */

float			*init_zbuffer(t_game *game);
void			init_column(t_column *col, int x, float perp, int screen_h);
void			init_ray(t_ray *ray, t_player *player, float ray_angle,
					t_data *target);
void			init_camera(t_camera *camera, t_player *player);

/* -----------------------camera related functions ----------------------- */

void			rotate_camera(t_camera *camera, float angle);
void			move_camera(t_camera *camera, t_map *map, float move_step);
void			get_camera_ray(t_camera *camera, int x, t_ray *ray);
void			update_camera(t_camera *camera, t_player *player);

/* -------------------ray casting utilities ------------------- */

int				validate_trace_inputs(t_ray *ray, t_minimap *map,
					t_dcoord *hit_point);
float			perp_dist_from_proj(const t_ray *ray,
					const t_dcoord cam_dir_u);
int				compute_line_height(int screen_h, float perp_dist);
void			clamp_draw_bounds(int line_h, int screen_h,
					int *draw_start, int *draw_end);
t_image			*get_directional_texture(t_game *game);

/* -------------------column related functions -------------------*/

void			cast_single_column(t_game *game, t_data *data,
					t_camera *camera, int x);
unsigned int	get_column_color(t_game *game, t_column *col,
					t_image *tex, int y);
void			draw_column_pixels(t_game *game, t_data *data, t_column *col,
					t_image *tex);
void			render_wall_column(t_game *game, t_data *data, int x,
					float perp);

/* -------------------color related functions -------------------*/

unsigned int	color_to_hex(t_color color);
t_color			hex_to_color(unsigned int hex);
t_color			apply_shade(t_color color, float shade);
t_color			apply_side_darkening(t_color color, int side);
float			calculate_shade_factor(float distance, float shadow_k,
					float light_intensity);

#endif