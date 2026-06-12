/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:14:07 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/09 19:09:11 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/**
 * auxiliary function to rotate a vector by a given angle
 * @param v The input vector to rotate
 * @param a The angle to rotate by (in radians)
 * @param out The output vector after rotation
 */
static void	rotate_ray(t_dcoord v, double a, t_dcoord *out)
{
	double	cos_a;
	double	sin_a;

	cos_a = cos(a);
	sin_a = sin(a);
	out->x = v.x * cos_a - v.y * sin_a;
	out->y = v.x * sin_a + v.y * cos_a;
}

/**
 * function to set up the left and right rays for the player's 
 * field of view (FOV). It calculates the direction of the left 
 * and right rays by rotating the player's direction vector by
 * half of the FOV angle in both directions. The left 
 * ray is rotated by the negative half FOV angle, while
 * the right ray is rotated by the positive half FOV angle. The
 * function initializes both rays using the init_ray function,
 * setting their angles based on the rotated direction vectors.
 */
static void	set_fov_rays(t_player *player, t_ray *left,
			t_ray *right, t_data *target)
{
	t_dcoord	rotated;
	t_dcoord	dir;
	float		fov;
	float		half_fov;

	fov = 66.0f * (PI / 180.0f);
	half_fov = fov / 2.0f;
	dir = (t_dcoord){cosf(player->angle), sinf(player->angle)};
	rotate_ray(dir, -half_fov, &rotated);
	init_ray(left, player, atan2f(rotated.y, rotated.x), target);
	left->color = YELLOW;
	rotate_ray(dir, half_fov, &rotated);
	init_ray(right, player, atan2f(rotated.y, rotated.x), target);
	right->color = YELLOW;
}

void	draw_fov_rays(t_player *player, t_minimap *map, t_data *target)
{
	t_ray	left_ray;
	t_ray	right_ray;

	if (!player || !map || !target)
		return ;
	ft_bzero(&left_ray, sizeof(t_ray));
	ft_bzero(&right_ray, sizeof(t_ray));
	set_fov_rays(player, &left_ray, &right_ray, target);
	render_ray(&left_ray, map);
	render_ray(&right_ray, map);
}
