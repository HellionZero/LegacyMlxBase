/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_input.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:49:45 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/29 15:17:19 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_INPUT_H
# define CUB_INPUT_H

# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119

int		is_arrow_key(int keycode);
void	handle_arrow_press(int keycode, t_player *player, t_game *game);
int		is_direction_key(int keycode);
void	handle_direction_press(int keycode, t_player *player, t_game *game);

#endif