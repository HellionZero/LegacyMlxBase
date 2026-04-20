/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:26:20 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/20 18:37:03 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_RENDER_H
# define CUB_RENDER_H

# include "cub_structs.h"

/* ------------------ custom rendering functions ------------------ */

/* custom function to put a pixel on the screen */
void		mlx_put_pixel(t_data *data, int x, int y, int color);

/* custom function to remove a pixel from the screen */
void		mlx_remove_pixel(t_data *data, int x, int y);

/* function to clear the image buffer*/
void		clear_buffer(t_data *data, int color);

/* function to draw a single line between two points
using Bresenham's line algorithm */
void		draw_line(t_data *data, t_icoord start, t_icoord end, int color);

/* function to draw a filled rectangle given a position,
dimensions, and color */
t_rectangle	draw_rectangle(t_data *data, t_icoord pos, t_dim dim, int color);

/* function to draw a empty circle given a center,
radius, and color */
void		draw_circle(t_data *data, t_icoord center, int radius, int color);

/* function to draw a empty polygon given an array of points,
number of points, and color */
void		draw_polygon(t_data *data, t_icoord *points,
				int num_points, int color);

/* function to render the current frame by putting the image to the window */
void		render_frame(t_data *data, void *mlx_ptr, void *win_ptr);

/* function to free the pixel data and destroy the image */
void		free_pixel_data(t_data *data, void *mlx_ptr);

/* ------------ helper functions for Bresenham's line algorithm --------------*/
t_icoord	calcule_delta(t_icoord start, t_icoord end);
t_icoord	calcule_step(t_icoord start, t_icoord end);

void		calculate_pivot_points(t_rectangle *rect);

t_image		*load_texture(void *mlx_ptr, char *path);
void		render_texture(t_data *data, t_image *texture, t_icoord pos);
void		draw_textured_rectangle(t_data *data, t_icoord pos, t_dim dim,
				t_image *texture);
void		remove_texture(void *mlx_ptr, t_image *texture);

#endif