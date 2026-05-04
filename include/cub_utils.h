/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:44:58 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/29 19:44:05 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_UTILS_H
# define CUB_UTILS_H

# include "cub_structs.h"

void		init_timer(t_timer *timer);
void		update_timer(t_timer *timer);
float		set_step(float delta_time, float base_speed);

t_player	*create_player(void);
void		destroy_player(t_player *player);

void		remove_minimap_data(t_minimap *minimap);
t_minimap	*create_minimap(t_game *game);
void		destroy_minimap(t_minimap *minimap);
void		render_minimap(t_minimap *minimap, t_game *game, int wall_count);
void		composite_minimap_to_main(t_data *main_buffer, t_minimap *minimap);
void		calculate_minimap_offset(t_minimap *minimap, t_game *game);
void		set_minimap_addresses(t_data *main_buffer, t_minimap *mmap,
				t_icoord *pos, t_icoord *dst);
void		render_player_and_ray(t_game *game, t_minimap *minimap);
void		draw_player_on_minimap(t_minimap *minimap, t_game *game);

#endif