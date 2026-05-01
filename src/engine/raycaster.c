/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 15:51:56 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/01 20:04:17 by lsarraci         ###   ########.fr       */
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

t_dcoord	camera_dir_unit(const t_camera *camera)
{
	double	mag;

	mag = sqrt(camera->dir.x * camera->dir.x + camera->dir.y * camera->dir.y);
	if (mag > 0.0)
		return ((t_dcoord){camera->dir.x / mag, camera->dir.y / mag});
	return ((t_dcoord){0.0, 0.0});
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

double	frac_wall_x(const t_image *tex, double wall_x, int side,
			const t_ray *ray)
{
	double	wall_x_d;
	int		tex_x;

	(void)tex;
	wall_x_d = wall_x - floor(wall_x);
	tex_x = (side == 0 && ray->fdir.x > 0) || (side == 1 && ray->fdir.y < 0);
	if (tex_x)
		wall_x_d = 1.0 - wall_x_d;
	return (wall_x_d);
}

int	texture_x_from_wall(const t_image *tex, double wall_x, t_icoord t)
{
	double	wall_x_d;
	int		tex_x;

	wall_x_d = wall_x - floor(wall_x);
	tex_x = (int)(wall_x_d * (double)tex->dim.width);
	if ((t.x == 0 && t.y == 1) || (t.x == 1 && t.y == 0))
		tex_x = tex->dim.width - tex_x - 1;
	return (tex_x);
}

unsigned int	sample_texture_pixel(const t_image *tex, t_icoord t)
{
	int	tex_y;

	tex_y = (t.y - t.x) * tex->dim.height
		/ compute_line_height(tex->data.height, t.y);
	return (*(unsigned int *)(tex->addr + (tex_y * tex->data.line_length
			+ t.x * (tex->data.bits_per_pixel / 8))));
}

unsigned int	sample_shade_pixel(unsigned int color, float dist,
					int side, const t_game *game)
{
	float	shadow_k;
	float	light_intensity;
	float	shade;
	t_color	tex_color;
	t_color	shaded_color;

	if (game)
	{
		shadow_k = game->config.shadow_factor;
		light_intensity = game->config.light_intensity;
	}
	else
	{
		shadow_k = 0.25f;
		light_intensity = 1.0f;
	}
	shade = calculate_shade_factor(dist, shadow_k, light_intensity);
	tex_color = hex_to_color(color);
	shaded_color = apply_side_darkening(tex_color, side);
	shaded_color = apply_shade(shaded_color, shade);
	return (color_to_hex(shaded_color));
}

void	draw_textured_column(t_game *game, t_data *data, int x, t_icoord t,
			int line_h, int tex_x, float perp)
{
	t_image			*tex;
	t_point			draw_bounds;
	int				tex_y;
	unsigned int	color;

	(void)t;
	tex = game->wall_texture;
	clamp_draw_bounds(line_h, data->height, &draw_bounds.start,
		&draw_bounds.end);
	tex_y = draw_bounds.start;
	while (tex_y <= draw_bounds.end)
	{
		color = sample_texture_pixel(tex, (t_icoord){tex_x, tex_y});
		color = sample_shade_pixel(color, perp, game->ray.hit_side, game);
		mlx_put_pixel(data, x, tex_y, color);
		tex_y++;
	}
}

void	draw_flat_column(t_game *game, t_data *data, int x, t_icoord t,
			int line_h, unsigned int base_color, float perp)
{
	t_point			draw_bounds;
	int				y;
	char			cell;
	t_render_cfg	cfg;

	(void)t;
	if (game && game->map && game->ray.pos.y >= 0
		&& game->ray.pos.y < game->map->dim.height
		&& game->ray.pos.x >= 0 && game->ray.pos.x < game->map->dim.width)
	{
		cell = game->map->grid[game->ray.pos.y][game->ray.pos.x];
		(void)cell;
		base_color = 0xAAAAAA;
	}
	clamp_draw_bounds(line_h, data->height, &draw_bounds.start,
		&draw_bounds.end);
	y = draw_bounds.start;
	while (y <= draw_bounds.end)
	{
		if (game)
		{
			cfg.shadow_k = game->config.shadow_factor;
			cfg.light_intensity = game->config.light_intensity;
		}
		else
		{
			cfg.shadow_k = 0.25f;
			cfg.light_intensity = 1.0f;
		}
		cfg.shade = calculate_shade_factor(perp, cfg.shadow_k,
				cfg.light_intensity);
		cfg.base_color = hex_to_color(base_color);
		cfg.shade_color = apply_side_darkening(cfg.base_color,
				game->ray.hit_side);
		cfg.shade_color = apply_shade(cfg.shade_color, cfg.shade);
		cfg.shaded_hex = color_to_hex(cfg.shade_color);
		mlx_put_pixel(data, x, y, cfg.shaded_hex);
		y++;
	}
}

void	render_wall_column(t_game *game, t_data *data, int x, float perp)
{
	int				line_h;
	t_icoord		t;
	unsigned int	base_color;
	double			wall_x;
	int				tex_x;

	line_h = compute_line_height(data->height, perp);
	t.x = x;
	t.y = line_h;
	if (game->wall_texture)
	{
		if (game->ray.hit_side == 0)
			wall_x = game->ray.hit.y + fmod(game->ray.hit.y, 1.0);
		else
			wall_x = game->ray.hit.x + fmod(game->ray.hit.x, 1.0);
		tex_x = texture_x_from_wall(game->wall_texture, wall_x, t);
		draw_textured_column(game, data, x, t, line_h, tex_x, perp);
	}
	else
	{
		base_color = 0xFFFFFF;
		draw_flat_column(game, data, x, t, line_h, base_color, perp);
	}
}

void	render_minimap_debug_ray(t_game *game)
{
	if (!game || !game->ray.player)
		return ;
	draw_ray_on_minimap(&game->ray, game->minimap, &game->ray.hit);
}

void	cast_single_column(t_game *game, t_data *data, t_camera *camera, int x)
{
	float	perp;

	get_camera_ray(camera, x, &game->ray);
	trace_ray(&game->ray, game->minimap, &game->ray.hit);
	perp = perp_dist_from_proj(&game->ray, camera_dir_unit(camera));
	render_wall_column(game, data, x, perp);
}

void	cast_ray(t_game *game, t_data *data)
{
	t_camera	camera;
	int			x;

	x = 0;
	if (!game || !data)
		return ;
	game->ray.data = data;
	game->ray.player = game->player;
	init_camera(&camera, game->player);
	while (x < data->width)
		cast_single_column(game, data, &camera, x++);
}
