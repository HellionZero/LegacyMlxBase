/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:08:49 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/29 14:10:18 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <sys/time.h>
# include "../lib/libft/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include "cub_structs.h"
# include "cub_types.h"
# include "cub_utils.h"
# include "cub_render.h"
# include "cub_debug.h"
# include "cub_input.h"
# include "cub_engine.h"

int			handle_key_press(int keycode, void *param);
int			handle_close(void *param);
int			render(void *param);
void		initialize_image_data(t_window *window, int width, int height);
void		initialize_window_data(t_window *window, int width,
				int height, char *title);
t_window	*create_window(int width, int height, char *title);
void		close_window(void *param);
void		setup_hooks(void *param);
void		free_game(t_game *game);
void		init_game(t_game *game);
void		init_timer(t_timer *timer);
void		update_timer(t_timer *timer);

#endif