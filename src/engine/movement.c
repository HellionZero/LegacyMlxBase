/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:36:55 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/30 14:03:31 by lsarraci         ###   ########.fr       */
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
	t_dcoord	new_pos_x;
	t_dcoord	new_pos_y;

	if (!player || !map)
		return ;
	new_pos_x.x = player->pos.x + (move_step * cosf(player->angle));
	new_pos_x.y = player->pos.y;
	if (!rect_collides(map, new_pos_x, player->collision_radius))
		player->pos.x = new_pos_x.x;
	else
		fprintf(stderr, "move_player: blocked X\n");
	new_pos_y.x = player->pos.x;
	new_pos_y.y = player->pos.y + (move_step * sinf(player->angle));
	if (!rect_collides(map, new_pos_y, player->collision_radius))
	{
		player->pos.y = new_pos_y.y;
	}
	else
		fprintf(stderr, "move_player: blocked Y\n");
}

void	strafe_player(t_player *player, t_map *map, float move_step)
{
	t_dcoord	new_pos_x;
	t_dcoord	new_pos_y;

	if (!player || !map)
		return ;
	new_pos_x.x = player->pos.x + (move_step * cosf(player->angle + PI / 2));
	new_pos_x.y = player->pos.y;
	if (!rect_collides(map, new_pos_x, player->collision_radius))
		player->pos.x = new_pos_x.x;
	else
		fprintf(stderr, "strafe_player: blocked X\n");
	new_pos_y.x = player->pos.x;
	new_pos_y.y = player->pos.y + (move_step * sinf(player->angle + PI / 2));
	if (!rect_collides(map, new_pos_y, player->collision_radius))
		player->pos.y = new_pos_y.y;
	else
		fprintf(stderr, "strafe_player: blocked Y\n");
}

void	set_directional_movement(int keycode, t_player *player, t_game *game)
{
	float	move_step;
	float	speed;
	float	dt;

	speed = 3.0f;
	dt = 1.0f / 60.0f;
	if (game)
	{
		if (game->timer.delta_time > 0.0f)
			dt = game->timer.delta_time;
		else
			game->timer.delta_time = dt;
	}
	move_step = set_step(dt, speed);
	if (keycode == KEY_W)
		move_player(player, game->map, move_step);
	else if (keycode == KEY_S)
		move_player(player, game->map, -move_step);
	else if (keycode == KEY_A)
		strafe_player(player, game->map, -move_step);
	else if (keycode == KEY_D)
		strafe_player(player, game->map, move_step);
}
