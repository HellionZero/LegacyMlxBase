/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:08:49 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/18 17:28:22 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

# define PI 3.14159265358979323846

# include <stdio.h>
# include <stdlib.h>
# include "../lib/libft/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include "cub_structs.h"
# include "cub_render.h"

int			handle_key_press(int keycode, void *param);
int			handle_close(void *param);
t_window	*create_window(int width, int height, char *title);
void		close_window(void *param);
void		setup_hooks(void *param);
void		free_game(t_game *game);

#endif