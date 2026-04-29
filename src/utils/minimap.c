/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:04:52 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/29 18:19:20 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	remove_minimap_data(t_minimap *minimap)
{
	free(minimap->buffer);
	free(minimap);
}

static void	set_minimap_image(t_minimap *minimap)
{
	if (!minimap || !minimap->mlx_ptr)
		return ;
	minimap->buffer->img = mlx_new_image(minimap->mlx_ptr, minimap->dim.width,
			minimap->dim.height);
	if (!minimap->buffer->img)
	{
		ft_putstr_fd("Failed to create minimap image\n", 2);
		return ;
	}
	minimap->buffer->addr = mlx_get_data_addr(minimap->buffer->img,
			&minimap->buffer->bits_per_pixel,
			&minimap->buffer->line_length, &minimap->buffer->endian);
	if (!minimap->buffer->addr)
	{
		ft_putstr_fd("Failed to get minimap address\n", 2);
		mlx_destroy_image(minimap->mlx_ptr, minimap->buffer->img);
		minimap->buffer->img = NULL;
		return ;
	}
}

static void	initialize_minimap_data(t_minimap *minimap, t_game *game)
{
	minimap->buffer->width = 150;
	minimap->buffer->height = 150;
	minimap->buffer->bits_per_pixel = 32;
	minimap->buffer->line_length = minimap->buffer->width
		* (minimap->buffer->bits_per_pixel / 8);
	minimap->mlx_ptr = game->window->mlx_ptr;
	minimap->dim = (t_dim){150, 150};
	minimap->pos = (t_icoord){50, 50};
	minimap->offset = (t_icoord){0, 0};
	minimap->scale = 20.0f;
	minimap->ref_map = game->map;
	if (game->player)
		minimap->player_pos = (t_icoord){(int)(game->player->pos.x + 0.5),
			(int)(game->player->pos.y + 0.5)};
}

t_minimap	*create_minimap(t_game *game)
{
	t_minimap	*minimap;

	if (!game || !game->window || !game->window->mlx_ptr)
		return (NULL);
	minimap = malloc(sizeof(t_minimap));
	if (!minimap)
		return (NULL);
	minimap->buffer = malloc(sizeof(t_data));
	if (!minimap->buffer)
	{
		free(minimap);
		return (NULL);
	}
	initialize_minimap_data(minimap, game);
	set_minimap_image(minimap);
	if (!minimap->buffer->img || !minimap->buffer->addr)
	{
		remove_minimap_data(minimap);
		return (NULL);
	}
	minimap->buffer->tmp_img = NULL;
	return (minimap);
}

void	destroy_minimap(t_minimap *minimap)
{
	if (minimap)
	{
		if (minimap->buffer)
		{
			if (minimap->buffer->img && minimap->mlx_ptr)
				mlx_destroy_image(minimap->mlx_ptr, minimap->buffer->img);
			free(minimap->buffer);
		}
		free(minimap);
	}
}
