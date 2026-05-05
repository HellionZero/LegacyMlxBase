/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_column.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:41:31 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/05 17:40:03 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	cast_single_column(t_game *game, t_data *data, t_camera *camera, int x)
{
	float	perp;

	get_camera_ray(camera, x, &game->ray);
	trace_ray(&game->ray, game->minimap, &game->ray.hit);
	perp = perp_dist_from_proj(&game->ray, camera_dir_unit(camera));
	render_wall_column(game, data, x, perp);
}

unsigned int	get_column_color(t_game *game, t_column *col,
					t_image *tex, int y)
{
	int				pos_in_wall;
	unsigned int	color;

	if (!tex)
		return (0xFFFFFF);
	pos_in_wall = y - (col->screen_h - col->line_h) / 2;
	if (pos_in_wall >= 0 && pos_in_wall < col->line_h)
		color = *(unsigned int *)(tex->addr + ((pos_in_wall
						* tex->dim.height
						/ col->line_h) * tex->data.line_length
					+ col->tex_x * (tex->data.bits_per_pixel / 8)));
	else
		color = 0x000000;
	return (sample_shade_pixel(color, col->perp, game->ray.hit_side, game));
}

void	draw_column_pixels(t_game *game, t_data *data,
		t_column *col, t_image *tex)
{
	t_point	draw_bounds;
	int		y;

	if (!game || !data || !col)
		return ;
	clamp_draw_bounds(col->line_h, data->height, &draw_bounds.start,
		&draw_bounds.end);
	y = draw_bounds.start;
	while (y <= draw_bounds.end)
	{
		mlx_put_pixel(data, col->x, y, get_column_color(game, col, tex, y));
		y++;
	}
}

void	render_wall_column(t_game *game, t_data *data, int x, float perp)
{
	t_column		col;
	t_image			*tex;
	double			wall_x;
	double			wall_x_frac;

	if (!game || !data)
		return ;
	init_column(&col, x, perp, data->height);
	tex = get_directional_texture(game);
	col.tex_x = 0;
	if (tex)
	{
		if (game->ray.hit_side == 0)
			wall_x = fmod(game->ray.hit.y, 1.0);
		else
			wall_x = fmod(game->ray.hit.x, 1.0);
		wall_x_frac = wall_x;
		if ((game->ray.hit_side == 0 && game->ray.fdir.x < 0)
			|| (game->ray.hit_side == 1 && game->ray.fdir.y > 0))
			wall_x_frac = 1.0 - wall_x_frac;
		col.tex_x = (int)(wall_x_frac * (double)tex->dim.width);
		if (col.tex_x >= tex->dim.width)
			col.tex_x = tex->dim.width - 1;
	}
	draw_column_pixels(game, data, &col, tex);
}
