/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:48:03 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/28 18:05:57 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	is_arrow_key(int keycode)
{
	return (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT
		|| keycode == KEY_RIGHT);
}

void	handle_arrow_press(int keycode)
{
	if (keycode == KEY_UP)
		printf("Up arrow pressed\n");
	else if (keycode == KEY_DOWN)
		printf("Down arrow pressed\n");
	else if (keycode == KEY_LEFT)
		printf("Left arrow pressed\n");
	else if (keycode == KEY_RIGHT)
		printf("Right arrow pressed\n");
}

int	is_direction_key(int keycode)
{
	return (is_arrow_key(keycode) || keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_D);
}

void	handle_direction_press(int keycode, t_player *player, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
		set_directional_movement(keycode, player, game);
	else
		handle_arrow_press(keycode);
}
