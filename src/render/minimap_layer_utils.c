/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_layer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:35:12 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/30 15:34:53 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

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
