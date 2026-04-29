/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:07:25 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/29 18:23:52 by lsarraci         ###   ########.fr       */
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
}

static void	trace_ray(t_ray *ray, t_minimap *map, t_dcoord *hit_point)
{
	int			max_distance;
	t_icoord	map_pos;

	max_distance = 1000;
	while (ray->length < max_distance)
	{
		map_pos.x = (int)ray->fpos.x;
		map_pos.y = (int)ray->fpos.y;
		if (map_pos.x < 0 || map_pos.x >= map->ref_map->dim.width
			|| map_pos.y < 0 || map_pos.y >= map->ref_map->dim.height)
			break ;
		if (map->ref_map->grid[map_pos.y][map_pos.x] == '1')
			break ;
		ray->fpos.x += ray->fdir.x * STEP_SIZE;
		ray->fpos.y += ray->fdir.y * STEP_SIZE;
		ray->length += STEP_SIZE;
	}
	ray->pos.x = (int)ray->fpos.x;
	ray->pos.y = (int)ray->fpos.y;
	ray->dir.x = (int)roundf(ray->fdir.x);
	ray->dir.y = (int)roundf(ray->fdir.y);
	*hit_point = (t_dcoord){ray->fpos.x, ray->fpos.y};
}

static void	draw_ray_on_minimap(t_ray *ray, t_minimap *map, t_player *player,
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
		draw_line(ray->data, start, end, RED);
}

void	render_first_ray(t_player *player, t_minimap *mmap, t_ray *ray)
{
	if (!player || !mmap || !ray || !mmap->ref_map || !mmap->ref_map->grid)
		return ;
	init_ray_for_player(ray, player, player->angle, mmap->buffer);
	trace_ray(ray, mmap, &ray->hit);
	draw_ray_on_minimap(ray, mmap, player, &ray->hit);
}
