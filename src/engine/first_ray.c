/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:07:25 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/01 17:11:31 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	init_ray(t_ray *ray, t_player *player, float ray_angle,
			t_data *target)
{
	ray->data = target;
	ray->player = player;
	ray->fpos = player->pos;
	ray->fdir.x = cosf(ray_angle);
	ray->fdir.y = sinf(ray_angle);
	ray->length = 0;
	ray->hit_wall = 0;
	ray->hit_sprite = 0;
	ray->color = RED;
}

static void	calc_side_dist(t_dda *dda, t_dcoord ray_pos)
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

static int	check_bounds(t_dda *dda, t_minimap *map)
{
	if (dda->rmap.x < 0 || dda->rmap.x >= map->ref_map->dim.width
		|| dda->rmap.y < 0 || dda->rmap.y >= map->ref_map->dim.height)
		return (0);
	return (1);
}

static void	update_ray_step(t_dda *dda)
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

static void	find_wall_hit(t_dda *dda, t_minimap *map)
{
	dda->hit = 0;
	while (!dda->hit)
	{
		update_ray_step(dda);
		if (!check_bounds(dda, map))
			break ;
		if (map->ref_map->grid[dda->rmap.y][dda->rmap.x] == '1')
		{
			dda->hit = 1;
			break ;
		}
	}
}

static void	update_ray_hit_data(t_ray *ray, t_dda *dda, t_dcoord *hit_point)
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

static int	validate_trace_inputs(t_ray *ray, t_minimap *map,
				t_dcoord *hit_point)
{
	if (!ray)
	{
		if (hit_point)
			*hit_point = (t_dcoord){0.0, 0.0};
		return (0);
	}
	if (!map || !map->ref_map || !map->ref_map->grid)
	{
		if (hit_point)
			*hit_point = ray->fpos;
		ray->length = 0.0f;
		return (0);
	}
	return (1);
}

void	trace_ray(t_ray *ray, t_minimap *map, t_dcoord *hit_point)
{
	t_dda	dda;

	if (!validate_trace_inputs(ray, map, hit_point))
		return ;
	init_dda_variables(ray, &dda.rd, &dda.rmap, &dda.delta_dist);
	dda.side = 0;
	dda.hit = 0;
	calc_side_dist(&dda, ray->fpos);
	find_wall_hit(&dda, map);
	if (map->ref_map->grid[dda.rmap.y][dda.rmap.x] == '1')
		update_ray_hit_data(ray, &dda, hit_point);
	else
	{
		ray->length = 0.0f;
		ray->hit = ray->fpos;
		if (hit_point)
			*hit_point = ray->hit;
	}
}

void	draw_ray_on_minimap(t_ray *ray, t_minimap *map, t_dcoord *hit_point)
{
	t_icoord	start;
	t_icoord	end;
	t_fcoord	cur;

	cur.x = hit_point->x;
	cur.y = hit_point->y;
	start.x = (int)(ray->player->pos.x * map->scale + map->offset.x);
	start.y = (int)(ray->player->pos.y * map->scale + map->offset.y);
	end.x = (int)(cur.x * map->scale + map->offset.x);
	end.y = (int)(cur.y * map->scale + map->offset.y);
	if (ray->data)
		draw_line(ray->data, start, end, ray->color);
}

void	render_ray(t_ray *ray, t_minimap *map)
{
	if (!ray || !map || !ray->player || !map->ref_map || !map->ref_map->grid)
		return ;
	trace_ray(ray, map, &ray->hit);
	draw_ray_on_minimap(ray, map, &ray->hit);
}

void	render_first_ray(t_player *player, t_minimap *mmap, t_ray *ray)
{
	if (!player || !mmap || !ray || !mmap->ref_map || !mmap->ref_map->grid)
		return ;
	init_ray(ray, player, player->angle, mmap->buffer);
	render_ray(ray, mmap);
}
