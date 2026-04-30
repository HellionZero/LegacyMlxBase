/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:01:40 by lsarraci          #+#    +#+        */
/*   Updated: 2026/04/28 18:34:35 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

t_map	temp_map(void)
{
	static char	*grid[] = {
		"11111111111",
		"10000000001",
		"1011000S001",
		"10000100001",
		"11111111111"
	};
	t_map		map;

	map.ceiling_color = 0x87CEEB;
	map.floor_color = 0x228B22;
	map.grid = grid;
	map.dim.width = 11;
	map.dim.height = 5;
	return (map);
}

static int	is_orientation_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_elements_position(t_game *game)
{
	t_icoord	pos;

	if (game->player && game->map && game->map->grid)
	{
		pos.y = 0;
		while (pos.y < game->map->dim.height)
		{
			pos.x = 0;
			while (pos.x < game->map->dim.width)
			{
				if (game->map->grid[pos.y]
					&& (is_orientation_char(game->map->grid[pos.y][pos.x])))
				{
					game->player->pos.x = pos.x;
					game->player->pos.y = pos.y;
					if (is_orientation_char(game->map->grid[pos.y][pos.x]))
						game->player->angle
							= set_start_angle(game->map->grid[pos.y][pos.x]);
					return ;
				}
				pos.x++;
			}
			pos.y++;
		}
	}
}

void	init_map(t_game *game)
{
	t_map		map;

	map = temp_map();
	game->map = malloc(sizeof(t_map));
	if (game->map)
	{
		game->map->grid = map.grid;
		game->map->dim = map.dim;
		game->map->floor_color = map.floor_color;
		game->map->ceiling_color = map.ceiling_color;
		fprintf(stderr, "init_map: game=%p map=%p map->grid=%p dim=(%d,%d)\n",
			(void*)game, (void*)game->map, (void*)game->map->grid,
			game->map->dim.width, game->map->dim.height);
	}
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
		pos.x = 0;
		while (pos.x < game->map->dim.width)
		{
			if (game->map->grid[pos.y] && game->map->grid[pos.y][pos.x] == '1')
				draw_rectangle(data,
					(t_icoord){pos.x * tile_size, pos.y * tile_size},
					(t_dim){tile_size - 2, tile_size - 2}, 0xFFFFFF);
			if (game->map->grid[pos.y]
				&& is_orientation_char(game->map->grid[pos.y][pos.x]))
				draw_rectangle(data, (t_icoord){pos.x * tile_size + 10,
					pos.y * tile_size + 10}, (t_dim){tile_size - 20,
					tile_size - 20}, 0x00FF00);
			pos.x++;
		}
		pos.y++;
	}
}
