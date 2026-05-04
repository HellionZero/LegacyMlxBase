/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:44:45 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/04 16:31:46 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	validate_trace_inputs(t_ray *ray, t_minimap *map,
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

float	perp_dist_from_proj(const t_ray *ray, const t_dcoord cam_dir_u)
{
	t_dcoord	v;

	v.x = ray->hit.x - ray->fpos.x;
	v.y = ray->hit.y - ray->fpos.y;
	return (v.x * cam_dir_u.x + v.y * cam_dir_u.y);
}

int	compute_line_height(int screen_h, float perp_dist)
{
	int	line_height;

	if (perp_dist > 0.0f)
		line_height = (int)((float)screen_h / perp_dist);
	else
		line_height = screen_h;
	if (line_height <= 0)
		line_height = 1;
	return (line_height);
}

void	clamp_draw_bounds(int line_h, int screen_h,
			int *draw_start, int *draw_end)
{
	*draw_start = -line_h / 2 + screen_h / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = line_h / 2 + screen_h / 2;
	if (*draw_end >= screen_h)
		*draw_end = screen_h - 1;
}

t_image	*get_directional_texture(t_game *game)
{
	if (!game || !game->map)
		return (NULL);
	if (game->ray.hit_side == 0)
	{
		if (game->ray.fdir.x > 0)
			return (game->map->east_texture);
		else
			return (game->map->west_texture);
	}
	else
	{
		if (game->ray.fdir.y > 0)
			return (game->map->south_texture);
		else
			return (game->map->north_texture);
	}
}
