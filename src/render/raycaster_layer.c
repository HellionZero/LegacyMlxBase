/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_layer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:17:30 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/04 16:31:35 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

t_dcoord	camera_dir_unit(const t_camera *camera)
{
	double	mag;

	mag = sqrt(camera->dir.x * camera->dir.x + camera->dir.y * camera->dir.y);
	if (mag > 0.0)
		return ((t_dcoord){camera->dir.x / mag, camera->dir.y / mag});
	return ((t_dcoord){0.0, 0.0});
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
	{
		cast_single_column(game, data, &camera, x++);
	}
}
