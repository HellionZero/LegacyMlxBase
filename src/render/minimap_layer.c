/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_layer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:20:34 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/28 17:11:31 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	set_minimap_grid(t_minimap *minimap, t_icoord grid_pos,
		t_icoord *screen_pos)
{
	t_dim	tile_dim;

	screen_pos->x = (int)((grid_pos.x * minimap->scale) + minimap->offset.x);
	screen_pos->y = (int)((grid_pos.y * minimap->scale) + minimap->offset.y);
	tile_dim.width = (int)minimap->scale;
	tile_dim.height = (int)minimap->scale;
	draw_rectangle(minimap->buffer, *screen_pos, tile_dim, 0xFFFFFF);
}

static void	set_minimap_player(t_minimap *minimap, t_game *game,
		t_icoord *screen_pos)
{
	t_dim	tile_dim;

	screen_pos->x = (int)((game->player->pos.x * minimap->scale)
			+ minimap->offset.x);
	screen_pos->y = (int)((game->player->pos.y * minimap->scale)
			+ minimap->offset.y);
	tile_dim.width = (int)(minimap->scale / 2);
	tile_dim.height = (int)(minimap->scale / 2);
	draw_rectangle(minimap->buffer, *screen_pos, tile_dim, GREEN);
}

void	render_minimap(t_minimap *minimap, t_game *game)
{
	t_icoord	grid_pos;
	t_icoord	screen_pos;

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
				set_minimap_grid(minimap, grid_pos, &screen_pos);
			grid_pos.x++;
		}
		grid_pos.y++;
	}
	if (game->player->pos.x >= 0 && game->player->pos.y >= 0)
		set_minimap_player(minimap, game, &screen_pos);
}

static void	set_buffer_to_address(t_data *main_buffer, t_data *minimap_buffer,
			t_icoord pos)
{
	char		*src_addr;
	char		*dst_addr;
	int			color;

	if (!main_buffer || !minimap_buffer)
		return ;
	src_addr = minimap_buffer->addr
		+ (pos.y * minimap_buffer->line_length
			+ pos.x * (minimap_buffer->bits_per_pixel / 8));
	color = *(int *)src_addr;
	dst_addr = main_buffer->addr
		+ (pos.y * main_buffer->line_length
			+ pos.x * (main_buffer->bits_per_pixel / 8));
	*(int *)dst_addr = color;
}

void	composite_minimap_to_main(t_data *main_buffer, t_minimap *mmap)
{
	t_icoord	pos;
	t_icoord	dst;

	if (!main_buffer || !mmap || !mmap->buffer)
		return ;
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
			{
				set_buffer_to_address(main_buffer, mmap->buffer, pos);
			}
			pos.x++;
		}
		pos.y++;
	}
}
