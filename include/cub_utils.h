/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:44:58 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/07 17:33:09 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_UTILS_H
# define CUB_UTILS_H

# include "cub_structs.h"

void		init_timer(t_timer *timer);
void		update_timer(t_timer *timer);
float		set_step(float delta_time, float base_speed);

/* --------- player helpers ---------*/

/* create a player. */
t_player	*create_player(void);

/*destroy a player and free its memory */
void		destroy_player(t_player *player);

/* --------- minimap helpers ---------*/

/* function to remove all data in the minimap buffer. 
the main use case it to clear the minimap before rendering the new frame */
void		remove_minimap_data(t_minimap *minimap);

/* function to create a minimap */
t_minimap	*create_minimap(t_game *game);

/* function to destroy all data in the minimap buffer */
void		destroy_minimap(t_minimap *minimap);

/* function to calculate the offset 
for the minimap based on the game state.
*/
void		calculate_minimap_offset(t_minimap *minimap, t_game *game);

#endif