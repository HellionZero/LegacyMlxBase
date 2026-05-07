/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_input.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:49:45 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/07 15:58:38 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_INPUT_H
# define CUB_INPUT_H

/* key codes */
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119

/* -----------------input handling functions --------------------*/

/* verify if the key is an arrow key */
int		is_arrow_key(int keycode);

/* handle the arrow key press and update the player's angle accordingly */
void	handle_arrow_press(int keycode, t_player *player, t_game *game);

/* verify if the key is a directional movement key (WASD) */
int		is_direction_key(int keycode);

/* handle the directional movement key press and update the player's 
position using the current angle as reference to the direction */
void	handle_direction_press(int keycode, t_player *player, t_game *game);

#endif