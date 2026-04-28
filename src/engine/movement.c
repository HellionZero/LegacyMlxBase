/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:36:55 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/28 17:59:10 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	is_position_walkable(t_map *map, float x, float y)
{
	int	grid_x;
	int	grid_y;

	if (!map || !map->grid)
		return (0);
	grid_x = (int)(x);
	grid_y = (int)(y);
	if (grid_y < 0 || grid_y >= map->dim.height
		|| grid_x < 0 || grid_x >= map->dim.width)
		return (0);
	if (map->grid[grid_y][grid_x] == '1')
		return (0);
	return (1);
}

void	move_player(t_player *player, t_map *map, float move_step)
{
	t_dcoord	new_pos;

	if (!player || !map)
		return ;
	new_pos.x = player->pos.x + (move_step * cos(player->dim.width));
	new_pos.y = player->pos.y + (move_step * sin(player->dim.width));
	if (is_position_walkable(map, new_pos.x, player->pos.y))
		player->pos.x = new_pos.x;
	if (is_position_walkable(map, player->pos.x, new_pos.y))
		player->pos.y = new_pos.y;
}

void	strafe_player(t_player *player, t_map *map, float move_step)
{
	t_dcoord	new_pos;

	if (!player || !map)
		return ;
	new_pos.x = player->pos.x + (move_step * cos(player->dim.width + PI / 2));
	new_pos.y = player->pos.y + (move_step * sin(player->dim.width + PI / 2));
	if (is_position_walkable(map, new_pos.x, player->pos.y))
		player->pos.x = new_pos.x;
	if (is_position_walkable(map, player->pos.x, new_pos.y))
		player->pos.y = new_pos.y;
}

void	set_directional_movement(int keycode, t_player *player, t_game *game)
{
	float	move_step;

	if (!player || !game || !game->map)
		return ;
	move_step = player->dim.width * 0.1f;
	if (keycode == KEY_W)
		move_player(player, game->map, move_step);
	else if (keycode == KEY_S)
		move_player(player, game->map, -move_step);
	else if (keycode == KEY_A)
		strafe_player(player, game->map, -move_step);
	else if (keycode == KEY_D)
		strafe_player(player, game->map, move_step);
}
