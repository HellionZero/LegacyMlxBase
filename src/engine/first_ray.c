/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:07:25 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/30 20:04:54 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	init_ray_for_player(t_ray *ray, t_player *player,
				float ray_angle, t_data *target)
{
	ray->data = target;
	ray->fpos = player->pos;
	ray->fdir.x = cosf(ray_angle);
	ray->fdir.y = sinf(ray_angle);
	ray->length = 0;
	ray->hit_wall = 0;
	ray->hit_sprite = 0;
	ray->color = RED;
}

void	trace_ray(t_ray *ray, t_minimap *map, t_dcoord *hit_point)
{
	t_icoord	rmap;
	t_dcoord	rd;
	t_dcoord	delta_dist;
	t_dcoord	side_dist;
	t_icoord	step;
	int			hit;
	int			side;
	double		perp_dist;

	hit = 0;
	side = 0;
	if (!ray)
	{
		if (hit_point)
			*hit_point = (t_dcoord){0.0, 0.0};
		return ;
	}
	if (!map || !map->ref_map || !map->ref_map->grid)
	{
		if (hit_point)
			*hit_point = ray->fpos;
		ray->length = 0.0f;
		return ;
	}
	init_dda_variables(ray, &rd, &rmap, &delta_dist);
	if (rd.x < 0)
	{
		step.x = -1;
		side_dist.x = (ray->fpos.x - rmap.x) * delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (rmap.x + 1.0 - ray->fpos.x) * delta_dist.x;
	}
	if (rd.y < 0)
	{
		step.y = -1;
		side_dist.y = (ray->fpos.y - rmap.y) * delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (rmap.y + 1.0 - ray->fpos.y) * delta_dist.y;
	}
	while (!hit)
	{
		/* bounds check */
		if (rmap.x < 0 || rmap.x >= map->ref_map->dim.width
			|| rmap.y < 0 || rmap.y >= map->ref_map->dim.height)
			break ;
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			rmap.x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			rmap.y += step.y;
			side = 1;
		}
		if (map->ref_map->grid[rmap.y][rmap.x] == '1')
		{
			hit = 1;
			break ;
		}
	}
	if (hit)
	{
		if (side == 0)
			perp_dist = (rmap.x - ray->fpos.x + (1 - step.x) / 2.0) / rd.x;
		else
			perp_dist = (rmap.y - ray->fpos.y + (1 - step.y) / 2.0) / rd.y;
		ray->hit.x = ray->fpos.x + rd.x * perp_dist;
		ray->hit.y = ray->fpos.y + rd.y * perp_dist;
		ray->pos.x = rmap.x;
		ray->pos.y = rmap.y;
		ray->hit_side = side;
		ray->dir.x = step.x;
		ray->dir.y = step.y;
		ray->length = (float)fabs(perp_dist);
		if (hit_point)
			*hit_point = ray->hit;
	}
	else
	{
		ray->length = 0.0f;
		ray->hit = ray->fpos;
		if (hit_point)
			*hit_point = ray->hit;
	}
}

void	draw_ray_on_minimap(t_ray *ray, t_minimap *map, t_player *player,
				t_dcoord *hit_point)
{
	t_icoord	start;
	t_icoord	end;
	t_fcoord	cur;

	cur.x = hit_point->x;
	cur.y = hit_point->y;
	start.x = (int)(player->pos.x * map->scale + map->offset.x);
	start.y = (int)(player->pos.y * map->scale + map->offset.y);
	end.x = (int)(cur.x * map->scale + map->offset.x);
	end.y = (int)(cur.y * map->scale + map->offset.y);
	if (ray->data)
		draw_line(ray->data, start, end, ray->color);
}

void	render_first_ray(t_player *player, t_minimap *mmap, t_ray *ray)
{
	if (!player || !mmap || !ray || !mmap->ref_map || !mmap->ref_map->grid)
		return ;
	init_ray_for_player(ray, player, player->angle, mmap->buffer);
	trace_ray(ray, mmap, &ray->hit);
	draw_ray_on_minimap(ray, mmap, player, &ray->hit);
}
