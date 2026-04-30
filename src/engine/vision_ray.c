/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:14:07 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/30 15:41:37 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	init_vision_ray(t_ray *ray, t_player *player,
				float ray_angle, t_data *target)
{
	ray->data = target;
	ray->fpos = player->pos;
	ray->fdir.x = cosf(ray_angle);
	ray->fdir.y = sinf(ray_angle);
	ray->length = 0;
	ray->hit_wall = 0;
	ray->hit_sprite = 0;
	ray->color = YELLOW;
}

static void	rotate_ray(t_dcoord v, double a, t_dcoord *out)
{
	double	cos_a;
	double	sin_a;

	cos_a = cos(a);
	sin_a = sin(a);
	out->x = v.x * cos_a - v.y * sin_a;
	out->y = v.x * sin_a + v.y * cos_a;
}

static void	set_fov_rays(t_player *player, t_ray *left,
			t_ray *right, t_data *target)
{
	t_dcoord	rotated;
	t_dcoord	dir;
	float		fov;
	float		half_fov;

	fov = 60.0f * (PI / 180.0f);
	half_fov = fov / 2.0f;
	dir = (t_dcoord){cosf(player->angle), sinf(player->angle)};
	rotate_ray(dir, -half_fov, &rotated);
	init_vision_ray(left, player, atan2f(rotated.y, rotated.x), target);
	rotate_ray(dir, half_fov, &rotated);
	init_vision_ray(right, player, atan2f(rotated.y, rotated.x), target);
}

void	draw_fov_rays(t_player *player, t_minimap *map, t_data *target)
{
	t_ray	left_ray;
	t_ray	right_ray;

	if (!player || !map || !target)
		return ;
	set_fov_rays(player, &left_ray, &right_ray, target);
	trace_ray(&left_ray, map, &left_ray.hit);
	trace_ray(&right_ray, map, &right_ray.hit);
	draw_ray_on_minimap(&left_ray, map, player, &left_ray.hit);
	draw_ray_on_minimap(&right_ray, map, player, &right_ray.hit);
}
