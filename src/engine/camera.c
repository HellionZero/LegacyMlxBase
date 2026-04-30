/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 15:58:35 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/30 16:19:06 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	init_camera(t_camera *camera, t_player *player)
{
	camera->pos = player->pos;
	camera->dir = (t_dcoord){cosf(player->angle), sinf(player->angle)};
	camera->plane = (t_dcoord){-camera->dir.y * 0.66f,
		camera->dir.x * 0.66f};
	camera->screen_dim = (t_icoord){WINDOW_WIDTH, WINDOW_HEIGHT};
	camera->inv_screen_width = 1.0f / (float)WINDOW_WIDTH;
}

void	rotate_camera(t_camera *camera, float angle)
{
	double		cos_a;
	double		sin_a;
	t_dcoord	old_dir;
	t_dcoord	old_plane;

	sin_a = sinf(angle);
	cos_a = cosf(angle);
	old_dir = camera->dir;
	camera->dir.x = old_dir.x * cos_a - old_dir.y * sin_a;
	camera->dir.y = old_dir.x * sin_a + old_dir.y * cos_a;
	old_plane = camera->plane;
	camera->plane.x = old_plane.x * cos_a - old_plane.y * sin_a;
	camera->plane.y = old_plane.x * sin_a + old_plane.y * cos_a;
}

void	move_camera(t_camera *camera, t_map *map, float move_step)
{
	t_dcoord	new_pos_x;
	t_dcoord	new_pos_y;

	if (!camera || !map)
		return ;
	new_pos_x.x = camera->pos.x + (move_step * camera->dir.x);
	new_pos_x.y = camera->pos.y;
	if (!rect_collides(map, new_pos_x, 0.1f))
		camera->pos.x = new_pos_x.x;
	else
		fprintf(stderr, "move_camera: blocked X\n");
	new_pos_y.x = camera->pos.x;
	new_pos_y.y = camera->pos.y + (move_step * camera->dir.y);
	if (!rect_collides(map, new_pos_y, 0.1f))
		camera->pos.y = new_pos_y.y;
	else
		fprintf(stderr, "move_camera: blocked Y\n");
}

void	get_camera_ray(t_camera *camera, int x, t_ray *ray)
{
	float	camera_x;

	camera_x = 2.0f * x * camera->inv_screen_width - 1.0f;
	ray->fpos = camera->pos;
	ray->fdir.x = camera->dir.x + camera->plane.x * camera_x;
	ray->fdir.y = camera->dir.y + camera->plane.y * camera_x;
	ray->length = 0;
	ray->hit_wall = 0;
	ray->hit_sprite = 0;
}

void	update_camera(t_camera *camera, t_player *player)
{
	camera->pos = player->pos;
	camera->dir = (t_dcoord){cosf(player->angle), sinf(player->angle)};
	camera->plane = (t_dcoord){-camera->dir.y * 0.66f,
		camera->dir.x * 0.66f};
}
