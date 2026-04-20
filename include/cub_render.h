/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:26:20 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/20 15:17:31 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_RENDER_H
# define CUB_RENDER_H

# include "cub_structs.h"

void		mlx_put_pixel(t_data *data, int x, int y, int color);
void		mlx_remove_pixel(t_data *data, int x, int y);
void		clear_buffer(t_data *data, int color);
void		draw_line(t_data *data, t_icoord start, t_icoord end, int color);
void		draw_rectangle(t_data *data, t_icoord pos, t_dim dim, int color);
void		render_frame(t_data *data, void *mlx_ptr, void *win_ptr);
void		free_pixel_data(t_data *data, void *mlx_ptr);
t_icoord	calcule_delta(t_icoord start, t_icoord end);
t_icoord	calcule_step(t_icoord start, t_icoord end);

#endif