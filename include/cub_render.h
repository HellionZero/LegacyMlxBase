/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:26:20 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/05 17:35:46 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_RENDER_H
# define CUB_RENDER_H

# include "cub_structs.h"

/* ------------------ custom rendering functions ------------------ */

/* custom function to put a pixel on the screen */
void			mlx_put_pixel(t_data *data, int x, int y, int color);

/* custom function to remove a pixel from the screen */
void			mlx_remove_pixel(t_data *data, int x, int y);

/* function to clear the image buffer*/
void			clear_buffer(t_data *data, int color);

/* function to draw a single line between two points
using Bresenham's line algorithm */
void			draw_line(t_data *data, t_icoord start, t_icoord end,
					int color);

/* function to draw a filled rectangle given a position,
dimensions, and color */
t_rectangle		draw_rectangle(t_data *data, t_icoord pos, t_dim dim,
					int color);

/* function to draw a empty circle given a center,
radius, and color */
void			draw_circle(t_data *data, t_icoord center, int radius,
					int color);

/* function to draw a empty polygon given an array of points,
number of points, and color */
void			draw_polygon(t_data *data, t_icoord *points,
					int num_points, int color);

/* function to render the current frame by putting the image to the window */
void			render_frame(t_data *data, void *mlx_ptr, void *win_ptr);

void			render_background(t_data *data, t_game *game);

/* function to free the pixel data and destroy the image */
void			free_pixel_data(t_data *data, void *mlx_ptr);

/* function to allocate and prepare image data */
t_data			*prepare_image_data(void *mlx_ptr, int width, int height);

/* ------------ helper functions for Bresenham's line algorithm --------------*/
t_icoord		calcule_delta(t_icoord start, t_icoord end);
t_icoord		calcule_step(t_icoord start, t_icoord end);

/* -------- function to calculate the pivot points of a 
rectangle for rotation and scaling -------------------------*/

void			calculate_pivot_points(t_rectangle *rect);

/*----------------------- texture management functions ------------------ */

t_image			*load_texture(void *mlx_ptr, char *path);
void			render_texture(t_data *data, t_image *texture, t_icoord pos);
void			draw_textured_rectangle(t_data *data, t_icoord pos, t_dim dim,
					t_image *texture);
void			remove_texture(void *mlx_ptr, t_image *texture);
t_image			*get_directional_texture(t_game *game);

/*----------------------- raycasting layer functions ------------------ */

t_dcoord		camera_dir_unit(const t_camera *camera);
unsigned int	sample_shade_pixel(unsigned int color, float dist,
					int side, const t_game *game);
void			cast_ray(t_game *game, t_data *data);

void			draw_tile_at(t_minimap *minimap, t_icoord pos,
					t_dim tile_dim, int color);
void			draw_grid_tile(t_minimap *minimap, t_icoord grid_pos);

void			render_minimap(t_minimap *minimap, t_game *game);
void			composite_minimap_to_main(t_data *main_buffer, t_minimap *minimap);

#endif