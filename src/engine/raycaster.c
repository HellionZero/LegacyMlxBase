/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 15:51:56 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/30 17:11:09 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

float	*init_zbuffer(t_game *game)
{
	float	*z_buffer;

	z_buffer = malloc(sizeof(float) * game->window->img_ptr->width);
	if (!z_buffer)
		return (0);
	return (z_buffer);
}
/*	
static float calc_perp_dist(t_ray *ray, t_dcoord hit_point)
{
	float perp_dist;
	{
		float dx = hit_point.x - ray->fpos.x;
		float dy = hit_point.y - ray->fpos.y;
		perp_dist = (dx * ray->fdir.x + dy * ray->fdir.y) /
			(ray->fdir.x * ray->fdir.x + ray->fdir.y * ray->fdir.y);
		perp_dist = fabsf(perp_dist);
	}
	if (perp_dist <= 0.000001f)
		perp_dist = 0.000001f;
	return (perp_dist);
}

static void	draw_wall_column(t_game *game, t_data *data, int x, float perp_dist)
{
	t_image		*tex;
	int		line_height;
	int		draw_start;
	int		draw_end;
	float	wall_x;
	int		tex_x;
	int		tex_y;
	int		side;
	unsigned int	color;

	tex = game->wall_texture;
	line_height = (int)((float)data->height / perp_dist);
	draw_start = -line_height / 2 + data->height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + data->height / 2;
	if (draw_end >= data->height)
		draw_end = data->height - 1;
	side = (fabs(game->ray.fdir.x) > fabs(game->ray.fdir.y)) ? 0 : 1;
	if (side == 0)
		wall_x = (float)(game->player->pos.y + perp_dist * game->ray.fdir.y);
	else
		wall_x = (float)(game->player->pos.x + perp_dist * game->ray.fdir.x);
	wall_x -= (float)floor(wall_x);

	if (tex && tex->img_ptr)
	{
		tex_x = (int)(wall_x * (float)tex->dim.width);
		if ((side == 0 && game->ray.fdir.x > 0)
			|| (side == 1 && game->ray.fdir.y < 0))
			tex_x = tex->dim.width - tex_x - 1;

		{
			int y = draw_start;
			while (y <= draw_end)
			{
				tex_y = (y - draw_start) * tex->dim.height / line_height;
				color = *(unsigned int *)(tex->addr
					+ (tex_y * tex->data.line_length + tex_x * (tex->data.bits_per_pixel / 8)));
				if (side == 1)
					color = (color >> 1) & 0x7F7F7F;
				mlx_put_pixel(data, x, y, color);
				y++;
			}
		}
	}
	else
	{
		unsigned int col = 0xFFFFFF;
		if (side == 1)
			col = 0x7F7F7F;
		{
			int y = draw_start;
			while (y <= draw_end)
			{
				mlx_put_pixel(data, x, y, col);
				y++;
			}
		}
	}
	game->ray.length = perp_dist;
}
void	cast_ray(t_game *game, t_data *data)
{
	int		x;
	t_camera	camera;

	if (!game || !data)
		return ;
	init_camera(&camera, game->player);

	for (x = 0; x < data->width; x++)
	{
		get_camera_ray(&camera, x, &game->ray);
		trace_ray(&game->ray, game->minimap, &game->ray.hit);
		{
			float perp = calc_perp_dist(&game->ray, game->ray.hit);
			if (perp <= 0.0f)
				perp = 0.0001f;
			draw_wall_column(game, data, x, perp);
			game->z_buffer[x] = perp;
		}
	}
} 
*/
