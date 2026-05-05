/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_layer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:35:12 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/05 17:32:30 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	draw_tile_at(t_minimap *minimap, t_icoord pos,
			t_dim tile_dim, int color)
{
	if (!minimap || !minimap->buffer)
		return ;
	draw_rectangle(minimap->buffer, pos, tile_dim, color);
}

void	draw_grid_tile(t_minimap *minimap, t_icoord grid_pos)
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

void	set_minimap_addresses(t_data *main_buffer, t_minimap *mmap,
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

void	render_player_and_ray(t_game *game, t_minimap *minimap)
{
	if (game->player->pos.x >= 0 && game->player->pos.y >= 0)
	{
		draw_player_on_minimap(minimap, game);
		render_first_ray(game->player, minimap, &game->ray);
		draw_fov_rays(game->player, minimap, minimap->buffer);
	}
}
