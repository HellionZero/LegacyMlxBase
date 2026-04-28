/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:44:58 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/28 16:43:52 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_UTILS_H
# define CUB_UTILS_H

# include "cub_structs.h"

void		init_timer(t_timer *timer);
void		update_timer(t_timer *timer);

t_player	*create_player(void);
void		destroy_player(t_player *player);

void		remove_minimap_data(t_minimap *minimap);
t_minimap	*create_minimap(t_game *game);
void		destroy_minimap(t_minimap *minimap);
void		render_minimap(t_minimap *minimap, t_game *game);
void		composite_minimap_to_main(t_data *main_buffer, t_minimap *minimap);
void		calculate_minimap_offset(t_minimap *minimap, t_game *game);

#endif