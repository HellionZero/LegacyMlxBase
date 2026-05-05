/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:44:56 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/05 17:27:34 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int	search_player_char(t_map *map, t_icoord *pos)
{
	int	len;

	pos->y = 0;
	while (pos->y < map->dim.height)
	{
		if (map->grid[pos->y])
		{
			len = ft_strlen(map->grid[pos->y]);
			pos->x = 0;
			while (pos->x < len)
			{
				if (is_orientation_char(map->grid[pos->y][pos->x]))
					return (1);
				pos->x++;
			}
		}
		pos->y++;
	}
	return (0);
}

static void	set_player_from_char(t_game *game, t_icoord pos)
{
	char	orientation_char;

	orientation_char = game->map->grid[pos.y][pos.x];
	game->player->pos.x = pos.x;
	game->player->pos.y = pos.y;
	game->player->angle = set_start_angle(orientation_char);
}

static void	set_elements_position(t_game *game)
{
	t_icoord	pos;

	if (!game->player || !game->map || !game->map->grid)
		return ;
	if (search_player_char(game->map, &pos))
		set_player_from_char(game, pos);
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
