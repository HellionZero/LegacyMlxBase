/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_layer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbara.drummond <barbara.drummond@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:20:34 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/09 23:27:27 by barbara.dru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	draw_player_on_minimap(t_minimap *minimap, t_game *game)
{
	t_dim		tile_dim;
	t_icoord	screen_pos;
	t_dcoord	p;
	int			width_px;

	if (!minimap || !game || !game->map || !game->map->player)
		return ;
	p.x = game->map->player->pos.x * minimap->scale;
	p.y = game->map->player->pos.y * minimap->scale;
	width_px = (int)roundf(game->map->player->collision_radius * 2.0f
			* minimap->scale);
	tile_dim.width = width_px;
	tile_dim.height = width_px;
	screen_pos.x = (int)(p.x + minimap->offset.x - (tile_dim.width / 2));
	screen_pos.y = (int)(p.y + minimap->offset.y - (tile_dim.height / 2));
	draw_tile_at(minimap, screen_pos, tile_dim, GREEN);
}

static void	draw_minimap_grid(t_minimap *minimap)
{
	t_icoord	grid_pos;
	int			len;

	grid_pos.y = 0;
	while (grid_pos.y < minimap->ref_map->dim.height)
	{
		if (minimap->ref_map->grid[grid_pos.y])
		{
			len = ft_strlen(minimap->ref_map->grid[grid_pos.y]);
			grid_pos.x = 0;
			while (grid_pos.x < len)
			{
				if (minimap->ref_map->grid[grid_pos.y][grid_pos.x] == '1')
					draw_grid_tile(minimap, grid_pos);
				grid_pos.x++;
			}
		}
		grid_pos.y++;
	}
}

static void	setup_minimap_render(t_minimap *minimap, t_game *game)
{
	calculate_minimap_offset(minimap, game);
	clear_buffer(minimap->buffer, 0x1a1a1a);
}

void	render_minimap(t_minimap *minimap, t_game *game)
{
	if (!minimap || !minimap->buffer || !minimap->ref_map
		|| !minimap->ref_map->grid || !game || !game->map
		|| !game->map->player)
		return ;
	setup_minimap_render(minimap, game);
	draw_minimap_grid(minimap);
	render_player_and_ray(game, minimap);
}

void	composite_minimap_to_main(t_data *main_buffer, t_minimap *mmap)
{
	t_icoord	pos;
	t_icoord	dst;

	pos.y = 0;
	while (pos.y < mmap->buffer->height)
	{
		pos.x = 0;
		while (pos.x < mmap->buffer->width)
		{
			dst.x = mmap->pos.x + pos.x;
			dst.y = mmap->pos.y + pos.y;
			if (dst.x >= 0 && dst.x < main_buffer->width
				&& dst.y >= 0 && dst.y < main_buffer->height)
				set_minimap_addresses(main_buffer, mmap, &pos, &dst);
			pos.x++;
		}
		pos.y++;
	}
}
