/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:26:20 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/07 17:29:27 by lsarraci         ###   ########.fr       */
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

/* function to render the background layer which contains the ceiling 
and ground colors */
void			render_background(t_data *data, t_game *game);

/* function to free the pixel data and destroy the image */
void			free_pixel_data(t_data *data, void *mlx_ptr);

/* function to allocate and prepare image data */
t_data			*prepare_image_data(void *mlx_ptr, int width, int height);

/* ------------ helper functions for Bresenham's line algorithm --------------*/

/*calcule delta: function to calculate the difference between two coordinates.
the main use of this value is to determine the length of the line */
t_icoord		calcule_delta(t_icoord start, t_icoord end);

/*calcule step: function to calculate the step for each axis.
the step is 1 or -1, and the main use of this value is 
to determine the direction of the line */
t_icoord		calcule_step(t_icoord start, t_icoord end);

/* function to calculate the pivot points of a rectangle, 
mainly used for rotation and scaling. subject to future 
use cases */
void			calculate_pivot_points(t_rectangle *rect);

/*----------------------- texture management functions ------------------ */

/*function to load a texture from a file */
t_image			*load_texture(void *mlx_ptr, char *path);

/* function to render a texture on the screen */
void			render_texture(t_data *data, t_image *texture, t_icoord pos);

/* function to draw a rectangle with a texture */
void			draw_textured_rectangle(t_data *data, t_icoord pos, t_dim dim,
					t_image *texture);

/* function to free a texture and its associated data */
void			remove_texture(void *mlx_ptr, t_image *texture);

/* function to get a directional texture based on the game state and ray 
data */
t_image			*get_directional_texture(t_game *game);

/*----------------------- raycasting layer functions ------------------ */

/* function to calculate the unit vector of the camera's direction.
the main use of this value is to determine the direction of the camera.

it uses a magnitude value to normalize the vector.
the magnitude is calculated using the Pythagorean theorem, and the unit vector is
calculated by dividing the camera's direction vector by its magnitude. 
then the magnitude is used to calculate the final unit vector, normalizing 
the values of the x and y direction of the camera.
this function is needed to determine the direction of the camera */
t_dcoord		camera_dir_unit(const t_camera *camera);

/* function to sample a shaded pixel based on its color, distance, and side.
returns the sampled pixel, utilizing color functions
to realize bitwise operations depending of the values
passed to this function. */
unsigned int	sample_shade_pixel(unsigned int color, float dist,
					int side, const t_game *game);

/* main function for raycasting. 
it initializes the camera and perform a loop to 
renderize each column */					
void			cast_ray(t_game *game, t_data *data);

/*------------ minimap layer functions ------------*/

/*function to draw tiles at given position, dimension and color. 
it checks if there is a buffer given to the minimap and utilizes
it to draw the tiles in the minimap buffer */
void			draw_tile_at(t_minimap *minimap, t_icoord pos,
					t_dim tile_dim, int color);

/* function to draw the tile on the grid. */
void			draw_grid_tile(t_minimap *minimap, t_icoord grid_pos);

/* draws the player tile on minimap, at a given position. */
void			draw_player_on_minimap(t_minimap *minimap, t_game *game);

/* function to set the addresses for the minimap rendering. */
void			set_minimap_addresses(t_data *main_buffer, t_minimap *mmap,
					t_icoord *pos, t_icoord *dst);

/* function to render the player and ray on the minimap. */
void			render_player_and_ray(t_game *game, t_minimap *minimap);

/* main function to render the minimap. 
it sets the offset of the minimap and clear the buffer at each frame,
draws the grid and set the player position*/
void			render_minimap(t_minimap *minimap, t_game *game);

/* function to composite the minimap onto the main buffer. */
void			composite_minimap_to_main(t_data *main_buffer,
					t_minimap *minimap);

#endif