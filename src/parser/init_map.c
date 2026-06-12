/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbara.drummond <barbara.drummond@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:44:56 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/09 23:31:18 by barbara.dru      ###   ########.fr       */
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

static void	set_player_from_char(t_map *map, t_icoord pos)
{
	char	orientation_char;

	orientation_char = map->grid[pos.y][pos.x];
	map->player->pos.x = pos.x;
	map->player->pos.y = pos.y;
	map->player->angle = set_start_angle(orientation_char);
}

void	init_player_from_grid(t_map *map)
{
	t_icoord	pos;

	if (!map || !map->player || !map->grid)
		return ;
	if (search_player_char(map, &pos))
		set_player_from_char(map, pos);
}

void	load_map_textures(t_game *game)
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
}
