/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:17:38 by bmoreira          #+#    #+#             */
/*   Updated: 2026/05/11 15:50:23 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	flood_fill(char **grid, int height, int y, int x)
{
	int		len;
	char	cell;

	if (y < 0 || y >= height)
		return (0);
	if (!grid[y])
		return (0);
	len = ft_strlen(grid[y]);
	if (x < 0 || x >= len)
		return (0);
	cell = grid[y][x];
	if (cell == ' ' || cell == '\t')
		return (0);
	if (cell == '1' || cell == 'V')
		return (1);
	if (cell != '0' && !is_orientation_char(cell))
		return (0);
	grid[y][x] = 'V';
	if (!flood_fill(grid, height, y - 1, x)
		|| !flood_fill(grid, height, y + 1, x)
		|| !flood_fill(grid, height, y, x - 1)
		|| !flood_fill(grid, height, y, x + 1))
		return (0);
	return (1);
}

static void	validate_allowed_chars(t_map *map, int y)
{
	int	x;
	int	player_count;

	if (!map || !map->grid)
		return ;
	player_count = 0;
	while (y < map->dim.height)
	{
		if (map->grid[y])
		{
			x = 0;
			while (map->grid[y][x])
			{
				if (!is_valid_map_char(map->grid[y][x]))
					error_handler(map, NULL, INVALID_GRID);
				if (is_orientation_char(map->grid[y][x]))
					player_count++;
				x++;
			}
		}
		y++;
	}
	if (player_count != 1)
		error_handler(map, NULL, INVALID_GRID);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == '\t' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == '\n');
}

void	validate_grid(t_map *map)
{
	char	**grid_dup;

	validate_allowed_chars(map, 0);
	if (!map || !map->grid || !map->player)
		return ;
	grid_dup = ft_matrix_dup(map->grid);
	if (!grid_dup)
		error_handler(map, NULL, JOIN_CONTENT);
	if (!flood_fill(grid_dup, map->dim.height,
			(int)map->player->pos.y, (int)map->player->pos.x))
		error_handler(map, grid_dup, INVALID_GRID);
	ft_free_split(grid_dup);
}
