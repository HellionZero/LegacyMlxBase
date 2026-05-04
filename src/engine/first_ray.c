/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:07:25 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/04 16:14:19 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

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

	if (!ray || !map || !ray->player || !hit_point || !ray->data)
		return ;
	start.x = (int)(ray->player->pos.x * map->scale + map->offset.x);
	start.y = (int)(ray->player->pos.y * map->scale + map->offset.y);
	end.x = (int)(hit_point->x * map->scale + map->offset.x);
	end.y = (int)(hit_point->y * map->scale + map->offset.y);
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
