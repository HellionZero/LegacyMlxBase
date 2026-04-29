/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:48:03 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/29 18:22:01 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	is_arrow_key(int keycode)
{
	return (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT
		|| keycode == KEY_RIGHT);
}

void	handle_arrow_press(int keycode, t_player *player, t_game *game)
{
	float	dt;

	if (!player || !game)
		return ;
	dt = game->timer.delta_time;
	if (dt <= 0.0f)
		dt = 1.0f / 60.0f;
	if (keycode == KEY_LEFT)
	{
		player->angle -= ROT_FACTOR * dt;
		if (player->angle < 0)
			player->angle += 2 * PI;
	}
	else if (keycode == KEY_RIGHT)
	{
		player->angle += ROT_FACTOR * dt;
		if (player->angle >= 2 * PI)
			player->angle -= 2 * PI;
	}
	else if (keycode == KEY_UP)
		return ;
	else if (keycode == KEY_DOWN)
		return ;
}

int	is_direction_key(int keycode)
{
	return (is_arrow_key(keycode) || keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_D);
}

void	handle_direction_press(int keycode, t_player *player, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_D)
	{
		set_directional_movement(keycode, player, game);
	}
	else
	{
		handle_arrow_press(keycode, player, game);
	}
}
