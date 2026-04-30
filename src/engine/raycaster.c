/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 15:51:56 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/30 17:32:49 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

float	*init_zbuffer(t_game *game)
{
	float	*z_buffer;

	if (!game || !game->window || !game->window->img_ptr)
		return (NULL);
	z_buffer = malloc(sizeof(float) * game->window->img_ptr->width);
	if (!z_buffer)
		return (NULL);
	return (z_buffer);
}

static float	calc_perp_dist(const t_ray *ray, const t_camera *camera)
{
	double vx = ray->hit.x - camera->pos.x;
	double vy = ray->hit.y - camera->pos.y;
	double cam_dx = camera->dir.x;
	double cam_dy = camera->dir.y;
	double cam_mag = sqrt(cam_dx * cam_dx + cam_dy * cam_dy);
	if (cam_mag > 0.0)
	{
		cam_dx /= cam_mag;
		cam_dy /= cam_mag;
	}
	double proj = vx * cam_dx + vy * cam_dy;
	if (proj < 0.0)
		proj = -proj;
	if (proj < 1e-6)
		proj = 1e-6;
	return ((float)proj);
}

static void	draw_wall_column(t_game *game, t_data *data, int x, float perp_dist)
{
	t_image		*tex = game->wall_texture;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x_d;
	int		tex_x;
	int		tex_y;
	int		side;
	unsigned int	color;

	if (!data)
		return ;

	line_height = (int)((float)data->height / perp_dist);
	if (line_height <= 0)
		line_height = 1;
	draw_start = -line_height / 2 + data->height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + data->height / 2;
	if (draw_end >= data->height)
		draw_end = data->height - 1;



	/* use hit_side provided by trace_ray (0 = vertical/X side, 1 = horizontal/Y side) */
	side = game->ray.hit_side;
	if (side == 0)
		wall_x_d = game->ray.hit.y;
	else
		wall_x_d = game->ray.hit.x;
	wall_x_d = wall_x_d - floor(wall_x_d);

	if (tex && tex->img_ptr)
	{
		tex_x = (int)(wall_x_d * (double)tex->dim.width);
		if ((side == 0 && game->ray.fdir.x > 0) || (side == 1 && game->ray.fdir.y < 0))
			tex_x = tex->dim.width - tex_x - 1;

		int y = draw_start;
		while (y <= draw_end)
		{
			tex_y = (y - draw_start) * tex->dim.height / line_height;
			color = *(unsigned int *)(tex->addr + (tex_y * tex->data.line_length
				+ tex_x * (tex->data.bits_per_pixel / 8)));
			{
				float dist = perp_dist;
				/* stronger exponential falloff to make distance shading visible */
				float shadow_k = (game) ? game->config.shadow_factor : 0.25f; /* default stronger */
				if (shadow_k <= 0.0f) shadow_k = 0.25f;
				float shade = expf(-dist * shadow_k);
				/* side darkening */
				if (side == 1) shade *= 0.6f;
				/* global light intensity */
				shade *= (game) ? game->config.light_intensity : 1.0f;
				if (shade < 0.0f) shade = 0.0f;
				unsigned int r = (color >> 16) & 0xFF;
				unsigned int g = (color >> 8) & 0xFF;
				unsigned int b = (color) & 0xFF;
				unsigned int rr = (unsigned int)fminf(255.0f, r * shade + 0.5f);
				unsigned int gg = (unsigned int)fminf(255.0f, g * shade + 0.5f);
				unsigned int bb = (unsigned int)fminf(255.0f, b * shade + 0.5f);
				unsigned int shaded = (rr << 16) | (gg << 8) | bb;
				/* debug: print center column shade once per frame */
				if (x == data->width / 2)
					fprintf(stderr, "shade_debug x=%d dist=%.3f shade=%.3f tex=(%d,%d) color=0x%06X\n", x, dist, shade, tex_x, tex_y, color & 0xFFFFFF);
				mlx_put_pixel(data, x, y, shaded);
			}
			y++;
		}
	}
	else
	{
		/* fallback: shade a solid color based on map cell and distance */
		unsigned int base_color = 0xAAAAAA; /* default wall color */
		/* try to get map cell to select color */
		if (game && game->map && game->ray.pos.y >= 0 && game->ray.pos.y < game->map->dim.height
			&& game->ray.pos.x >= 0 && game->ray.pos.x < game->map->dim.width)
		{
			char cell = game->map->grid[game->ray.pos.y][game->ray.pos.x];
			(void)cell;
			/* can map different wall types here */
			base_color = 0xC0C0C0;
		}
		int y = draw_start;
		while (y <= draw_end)
		{
			/* compute shade similar to textured branch */
			float dist = perp_dist;
			float shadow_k = (game) ? game->config.shadow_factor : 0.25f;
			if (shadow_k <= 0.0f) shadow_k = 0.25f;
			float shade = expf(-dist * shadow_k);
			if (side == 1) shade *= 0.6f;
			shade *= (game) ? game->config.light_intensity : 1.0f;
			if (shade < 0.0f) shade = 0.0f;
			unsigned int r = (base_color >> 16) & 0xFF;
			unsigned int g = (base_color >> 8) & 0xFF;
			unsigned int b = base_color & 0xFF;
			unsigned int rr = (unsigned int)fminf(255.0f, r * shade + 0.5f);
			unsigned int gg = (unsigned int)fminf(255.0f, g * shade + 0.5f);
			unsigned int bb = (unsigned int)fminf(255.0f, b * shade + 0.5f);
			unsigned int shaded = (rr << 16) | (gg << 8) | bb;
			mlx_put_pixel(data, x, y, shaded);
			y++;
		}
	}

	/* record distance for sprite z-testing */
	game->ray.length = perp_dist;
}

void	cast_ray(t_game *game, t_data *data)
{
	int		x;
	t_camera	camera;
	t_data		*saved_ray_data;

	if (!game || !data)
		return ;

	/* prepare camera from player state and set screen width */
	init_camera(&camera, game->player);
	camera.screen_dim.x = data->width;
	camera.inv_screen_width = 1.0f / (float)data->width;

	x = 0;
	while (x < data->width)
	{
		get_camera_ray(&camera, x, &game->ray);
		/* trace on minimap to find hit point */
		trace_ray(&game->ray, game->minimap, &game->ray.hit);

		/* render this debug ray onto the minimap buffer */
			if (game->minimap && game->minimap->buffer)
		{
			saved_ray_data = game->ray.data;
			game->ray.data = game->minimap->buffer;
			draw_ray_on_minimap(&game->ray, game->minimap, game->player, &game->ray.hit);
			game->ray.data = saved_ray_data;
		}

		/* compute perpendicular distance and draw vertical slice */
		{
			/* compute perpendicular distance using hit point and camera to correct fish-eye */
			float perp = calc_perp_dist(&game->ray, &camera);
			if (perp <= 0.000001f)
				perp = 0.000001f;
			draw_wall_column(game, data, x, perp);
			if (game->z_buffer)
				game->z_buffer[x] = perp;
		}
		x++;
	}
}
