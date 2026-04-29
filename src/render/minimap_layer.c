/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_layer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:20:34 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/29 18:24:34 by lsarraci         ###   ########.fr       */
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
static void (*_ref_set_minimap_player)(t_minimap*, t_game*, t_icoord*) __attribute__((unused)) = set_minimap_player;

static void	set_minimap_player_centered(t_minimap *minimap, t_game *game, t_icoord *screen_pos)
{
	t_dim	tile_dim;
	float	px;
	float	yp;

	if (!minimap || !game || !game->player || !minimap->buffer)
		return ;
	px = (float)game->player->pos.x * minimap->scale;
	yp = (float)game->player->pos.y * minimap->scale;
	tile_dim.width = (int)(minimap->scale / 2.0f);
	tile_dim.height = (int)(minimap->scale / 2.0f);
	screen_pos->x = (int)(px + minimap->offset.x - (tile_dim.width / 2));
	screen_pos->y = (int)(yp + minimap->offset.y - (tile_dim.height / 2));
	draw_rectangle(minimap->buffer, *screen_pos, tile_dim, GREEN);
}

void	render_minimap(t_minimap *minimap, t_game *game)
{
	t_icoord	grid_pos;
	t_icoord	screen_pos;
	int			wall_count;

	calculate_minimap_offset(minimap, game);
	clear_buffer(minimap->buffer, 0x1a1a1a);
	grid_pos.y = 0;
	wall_count = 0;
	while (grid_pos.y < minimap->ref_map->dim.height)
	{
		grid_pos.x = 0;
		while (grid_pos.x < minimap->ref_map->dim.width)
		{
			if (minimap->ref_map->grid[grid_pos.y]
				&& minimap->ref_map->grid[grid_pos.y][grid_pos.x] == '1')
			{
				set_minimap_grid(minimap, grid_pos, &screen_pos);
				wall_count++;
			}
			grid_pos.x++;
		}
		grid_pos.y++;
	}
	if (game->player->pos.x >= 0 && game->player->pos.y >= 0)
	{
		set_minimap_player_centered(minimap, game, &screen_pos);
		render_first_ray(game->player, minimap, &game->ray);
	}
}

static void	set_minimap_addresses(t_data *main_buffer, t_minimap *mmap,
				t_icoord *pos, t_icoord *dst)
{
	char	*src_addr;
	char	*dst_addr;
	int		color;

	if (!main_buffer || !mmap || !mmap->buffer)
		return ;
	src_addr = mmap->buffer->addr + (pos->y * mmap->buffer->line_length
			+ pos->x * (mmap->buffer->bits_per_pixel / 8));
	color = *(int *)src_addr;
	dst_addr = main_buffer->addr + (dst->y * main_buffer->line_length
			+ dst->x * (main_buffer->bits_per_pixel / 8));
	*(int *)dst_addr = color;
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
