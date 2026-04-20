/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:01:40 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/20 17:24:22 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

t_map	temp_map(void)
{
	static char	*grid[] = {
		"11111111111",
		"10000000001",
		"1011000P001",
		"10000100001",
		"11111111111"
	};
	t_map		map;

	map.grid = grid;
	map.dim.width = 11;
	map.dim.height = 5;
	return (map);
}

void	render_temporary_map(t_game *game)
{
	int		x;
	int		y;
	t_map	map;

	map = temp_map();
	y = 0;
	while (y < map.dim.height)
	{
		x = 0;
		while (x < map.dim.width)
		{
			if (map.grid[y][x] == '1')
				draw_rectangle(game->window->img_ptr,
					(t_icoord){x * 42, y * 42},
					(t_dim){40, 40}, 0xFFFFFF);
			if (map.grid[y][x] == 'P')
				draw_rectangle(game->window->img_ptr,
					(t_icoord){x * 42, y * 42},
					(t_dim){10, 10}, BLUE);
			x++;
		}
		y++;
	}
}
