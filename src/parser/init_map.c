/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:44:56 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/05 16:51:22 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	set_elements_position(t_game *game)
{
	t_icoord	pos;
	int			len;

	if (!game->player || !game->map || !game->map->grid)
		return ;
	pos.y = 0;
	while (pos.y < game->map->dim.height)
	{
		if (game->map->grid[pos.y])
		{
			len = ft_strlen(game->map->grid[pos.y]);
			pos.x = 0;
			while (pos.x < len)
			{
				if (is_orientation_char(game->map->grid[pos.y][pos.x]))
				{
					game->player->pos.x = pos.x;
					game->player->pos.y = pos.y;
					game->player->angle
						= set_start_angle(game->map->grid[pos.y][pos.x]);
					return ;
				}
				pos.x++;
			}
		}
		pos.y++;
	}
}

void	load_map_textures_and_player(t_game *game)
{
	if (!game || !game->map || !game->window)
		return ;
	if (game->map->north_path)
		game->map->north_texture = load_texture(game->window->mlx_ptr,
				game->map->north_path);
	if (game->map->south_path)
		game->map->south_texture = load_texture(game->window->mlx_ptr,
				game->map->south_path);
	if (game->map->west_path)
		game->map->west_texture = load_texture(game->window->mlx_ptr,
				game->map->west_path);
	if (game->map->east_path)
		game->map->east_texture = load_texture(game->window->mlx_ptr,
				game->map->east_path);
	set_elements_position(game);
}

void	render_main_map(t_game *game, t_data *data)
{
	t_icoord	pos;
	int			tile_size;

	if (!game || !game->map || !data)
		return ;
	tile_size = 42;
	pos.y = 0;
	while (pos.y < game->map->dim.height)
	{
		if (!game->map->grid[pos.y])
		{
			pos.y++;
			continue ;
		}
		pos.x = 0;
		while (pos.x < (int)ft_strlen(game->map->grid[pos.y]))
		{
			if (game->map->grid[pos.y][pos.x] == '1')
				draw_rectangle(data,
					(t_icoord){pos.x * tile_size, pos.y * tile_size},
					(t_dim){tile_size - 2, tile_size - 2}, 0xFFFFFF);
			if (is_orientation_char(game->map->grid[pos.y][pos.x]))
				draw_rectangle(data, (t_icoord){pos.x * tile_size + 10,
					pos.y * tile_size + 10}, (t_dim){tile_size - 20,
					tile_size - 20}, 0x00FF00);
			pos.x++;
		}
		pos.y++;
	}
}
