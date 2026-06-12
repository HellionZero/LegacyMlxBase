/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:11:45 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/04 16:15:44 by lsarraci         ###   ########.fr       */
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

void	init_camera(t_camera *camera, t_player *player)
{
	camera->pos = player->pos;
	camera->dir = (t_dcoord){cosf(player->angle), sinf(player->angle)};
	camera->plane = (t_dcoord){-camera->dir.y * 0.66f,
		camera->dir.x * 0.66f};
	camera->screen_dim = (t_icoord){WINDOW_WIDTH, WINDOW_HEIGHT};
	camera->inv_screen_width = 1.0f / (float)WINDOW_WIDTH;
}

void	init_column(t_column *col, int x, float perp, int screen_h)
{
	if (!col)
		return ;
	col->x = x;
	col->line_h = compute_line_height(screen_h, perp);
	col->perp = perp;
	col->screen_h = screen_h;
}
