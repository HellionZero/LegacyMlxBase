/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_debug.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:06:23 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/04 17:03:59 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_DEBUG_H
# define CUB_DEBUG_H

# include "cub_structs.h"

int		count_map_rows(char **grid);
int		count_map_columns(char **grid);
int		is_orientation_char(char c);

t_map	temp_map(void);
void	init_map(t_game *game);
float	set_start_angle(char orientation);

#endif