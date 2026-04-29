/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_layer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:20:34 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/29 20:04:00 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	draw_tile_at(t_minimap *minimap, t_icoord pos,
			t_dim tile_dim, int color)
{
	if (!minimap || !minimap->buffer)
		return ;
	draw_rectangle(minimap->buffer, pos, tile_dim, color);
}

static void	draw_grid_tile(t_minimap *minimap, t_icoord grid_pos)
{
	t_dim		tile_dim;
	t_icoord	screen_pos;

	if (!minimap)
		return ;
	screen_pos.x = (int)((grid_pos.x * minimap->scale) + minimap->offset.x);
	screen_pos.y = (int)((grid_pos.y * minimap->scale) + minimap->offset.y);
	tile_dim.width = (int)minimap->scale;
	tile_dim.height = (int)minimap->scale;
	draw_tile_at(minimap, screen_pos, tile_dim, 0xFFFFFF);
}

void	draw_player_on_minimap(t_minimap *minimap, t_game *game)
{
	t_dim		tile_dim;
	t_icoord	screen_pos;
	t_dcoord	p;
	int			width_px;

	if (!minimap || !game || !game->player)
		return ;
	p.x = game->player->pos.x * minimap->scale;
	p.y = game->player->pos.y * minimap->scale;
	width_px = (int)roundf(game->player->collision_radius * 2.0f
			* minimap->scale);
	tile_dim.width = width_px;
	tile_dim.height = width_px;
	screen_pos.x = (int)(p.x + minimap->offset.x - (tile_dim.width / 2));
	screen_pos.y = (int)(p.y + minimap->offset.y - (tile_dim.height / 2));
	draw_tile_at(minimap, screen_pos, tile_dim, GREEN);
}

void	render_minimap(t_minimap *minimap, t_game *game, int wall_count)
{
	t_icoord	grid_pos;

	if (!minimap || !minimap->buffer || !minimap->ref_map
		|| !minimap->ref_map->grid || !game || !game->player)
		return ;
	calculate_minimap_offset(minimap, game);
	clear_buffer(minimap->buffer, 0x1a1a1a);
	grid_pos.y = 0;
	while (grid_pos.y < minimap->ref_map->dim.height)
	{
		grid_pos.x = 0;
		while (grid_pos.x < minimap->ref_map->dim.width)
		{
			if (minimap->ref_map->grid[grid_pos.y]
				&& minimap->ref_map->grid[grid_pos.y][grid_pos.x] == '1')
			{
				draw_grid_tile(minimap, grid_pos);
				wall_count++;
			}
			grid_pos.x++;
		}
		grid_pos.y++;
	}
	render_player_and_ray(game, minimap);
}

void	composite_minimap_to_main(t_data *main_buffer, t_minimap *mmap)
{
	t_icoord	pos;
	t_icoord	dst;
	int			pixel_count;

	pos.y = 0;
	pixel_count = 0;
	while (pos.y < mmap->buffer->height)
	{
		pos.x = 0;
		while (pos.x < mmap->buffer->width)
		{
			dst.x = mmap->pos.x + pos.x;
			dst.y = mmap->pos.y + pos.y;
			if (dst.x >= 0 && dst.x < main_buffer->width
				&& dst.y >= 0 && dst.y < main_buffer->height)
			{
				set_minimap_addresses(main_buffer, mmap, &pos, &dst);
				pixel_count++;
			}
			pos.x++;
		}
		pos.y++;
	}
}
