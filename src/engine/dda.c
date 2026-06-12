/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:58:30 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/09 18:57:11 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	init_dda_variables(t_ray *ray, t_dcoord *rd,
			t_icoord *rmap, t_dcoord *delta_dist)
{
	rd->x = ray->fdir.x;
	rd->y = ray->fdir.y;
	rmap->x = (int)floor(ray->fpos.x);
	rmap->y = (int)floor(ray->fpos.y);
	if (rd->x == 0.0)
		delta_dist->x = 1e10;
	else
		delta_dist->x = fabs(1.0 / rd->x);
	if (rd->y == 0.0)
		delta_dist->y = 1e10;
	else
		delta_dist->y = fabs(1.0 / rd->y);
}

void	calc_side_dist(t_dda *dda, t_dcoord ray_pos)
{
	if (dda->rd.x < 0)
	{
		dda->step.x = -1;
		dda->side_dist.x = (ray_pos.x - (int)ray_pos.x) * dda->delta_dist.x;
	}
	else
	{
		dda->step.x = 1;
		dda->side_dist.x = ((int)ray_pos.x + 1.0 - ray_pos.x)
			* dda->delta_dist.x;
	}
	if (dda->rd.y < 0)
	{
		dda->step.y = -1;
		dda->side_dist.y = (ray_pos.y - (int)ray_pos.y) * dda->delta_dist.y;
	}
	else
	{
		dda->step.y = 1;
		dda->side_dist.y = ((int)ray_pos.y + 1.0 - ray_pos.y)
			* dda->delta_dist.y;
	}
}

int	check_bounds(t_dda *dda, t_minimap *map)
{
	if (dda->rmap.x < 0 || dda->rmap.x >= map->ref_map->dim.width
		|| dda->rmap.y < 0 || dda->rmap.y >= map->ref_map->dim.height)
		return (0);
	return (1);
}

void	update_ray_hit_data(t_ray *ray, t_dda *dda, t_dcoord *hit_point)
{
	double	perp_dist;

	if (dda->side == 0)
		perp_dist = (dda->rmap.x - ray->fpos.x
				+ (1 - dda->step.x) / 2.0) / dda->rd.x;
	else
		perp_dist = (dda->rmap.y - ray->fpos.y
				+ (1 - dda->step.y) / 2.0) / dda->rd.y;
	ray->hit.x = ray->fpos.x + dda->rd.x * perp_dist;
	ray->hit.y = ray->fpos.y + dda->rd.y * perp_dist;
	ray->pos.x = dda->rmap.x;
	ray->pos.y = dda->rmap.y;
	ray->hit_side = dda->side;
	ray->dir.x = dda->step.x;
	ray->dir.y = dda->step.y;
	ray->length = (float)fabs(perp_dist);
	if (hit_point)
		*hit_point = ray->hit;
}

void	update_ray_step(t_dda *dda)
{
	if (dda->side_dist.x < dda->side_dist.y)
	{
		dda->side_dist.x += dda->delta_dist.x;
		dda->rmap.x += dda->step.x;
		dda->side = 0;
	}
	else
	{
		dda->side_dist.y += dda->delta_dist.y;
		dda->rmap.y += dda->step.y;
		dda->side = 1;
	}
}
