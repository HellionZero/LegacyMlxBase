/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_engine.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:56:15 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/09 17:42:34 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_ENGINE_H
# define CUB_ENGINE_H

# include "cub_structs.h"

/* ---------------------directional movement functions ------------------- */

/**
 * function to check if a given position is walkable (not a wall)
 * on the map. It converts the floating-point coordinates to grid
 * coordinates and checks the corresponding cell in the map grid.
 * If the cell contains '1', 
 * it is considered a wall and the function returns 0 (not walkable). 
 * Otherwise, it returns 1 (walkable).
 * @param map The map structure containing the grid and its dimensions.
 * @param x The x-coordinate of the position to check.
 * @param y The y-coordinate of the position to check.
 * @return 1 if the position is walkable, 0 if it is a wall or out of bounds.
*/
int				is_position_walkable(t_map *map, float x, float y);

/**
 * function to move the player forward or backward based on the current angle
 * and the specified movement step. It calculates the new position by adding
 * the movement step multiplied by the cosine of the angle for the x-coordinate
 * and the sine of the angle for the y-coordinate.
 * 
 * Before updating the player's position, it checks for collisions 
 * with walls using the rect_collides function.
 * 
 * If there is no collision, it updates the player's position accordingly.
 * 
 * @param player The player structure to move.
 * @param map The map structure containing the grid and its dimensions.
 * @param move_step The distance to move the player, where positive values
 * move forward and negative values move backward.
 */
void			move_player(t_player *player, t_map *map, float move_step);

/**
 * function to strafe the player left or right based on the current 
 * angle and the specified movement step. It calculates the new position
 * by adding the movement step multiplied by the cosine of the angle
 * plus 90 degrees for the x-coordinate and the sine of the angle
 * plus 90 degrees for the y-coordinate.
 * 
 * Similar to the move_player function, it checks for collisions with walls
 * before updating the player's position. If there is no collision, it updates
 * the player's position following the calculated new position.
 * 
 * @param player The player structure to strafe.
 * @param map The map structure containing the grid and its dimensions.
 * @param move_step The distance to strafe the player, where positive values
 * strafe right and negative values strafe left.
 */
void			strafe_player(t_player *player, t_map *map, float move_step);

/**
 * function to handle directional movement based on keyboard input.
 * It takes a keycode, the player structure, and the game structure
 * as parameters.
 * 
 * It calculates the movement step based on a base speed and
 * the delta time from the game timer. 
 * 
 * Depending on the keycode (W, A, S, D), it calls the
 * appropriate movement function (move_player or strafe_player)
 * with the calculated movement step to update the player's position.
 * @param keycode The keycode representing the directional input (W, A, S, D).
 * @param player The player structure to update based on the input.
 * @param game The game structure containing the timer
 * for delta time calculation.
*/
void			set_directional_movement(int keycode, t_player *player,
					t_game *game);

/* ------------------- collision detection functions ------------------- */

/**
 * Converts the player's position and collision radius
 * into a floating-point rectangle (t_frect).
 * 
 * It calculates the rectangle's width and height as twice the radius,
 * and sets the x and y coordinates to position the rectangle centered
 * around the player's position. This rectangle can then be used for
collision detection by sampling points within the rectangle and checking
for collisions with the map's walls.

 * @param pos The player's position as a t_dcoord.
 * @param radius The collision radius around the player.
 * @param out Output parameter to store the resulting t_frect.
*/
void			player_to_frect(t_dcoord pos, float radius, t_frect *out);

/**
 * function to sample a point within the floating-point rectangle.
 * it's needed to check for the collision at specific points within 
 * the rectangle, which represent the player's collision area.
 * The function takes the rectangle, two indices (i and j) to determine
 * which point to sample (top-left, center, bottom-right, etc.),
 * and an output t_dcoord to store the sampled point's coordinates.
 * The sample point is calculated based on the rectangle's position
 * and dimensions.
 * 
 * The indices i and j can range from 0 to 2, where (0,0) represents
 * the top-left corner of the rectangle, (1,1) represents the center 
 * and (2,2) represents the bottom-right corner. This allows for sampling
 * multiple points within the rectangle to check for collisions
 * at different locations around the player's position.
 * 
 * @param r The floating-point rectangle to sample from.
 * @param i The horizontal index for sampling (0 to 2).
 * @param j The vertical index for sampling (0 to 2).
 * @param out Output parameter to store the sampled point's coordinates.
*/
void			frect_sample_point(const t_frect *r, int i, int j,
					t_dcoord *out);

/**
 * function to to check if the floating-point rectangle collides 
 * with any walls on the map. It samples points within the rectangle 
 * using the frect_sample_point function and checks the
 * corresponding grid cells in the map's grid. If any of the sampled
 * points correspond to a wall (represented by a '1' in the grid),
 * the function returns 1 (indicating collision). 
 * if all sampled points are walkable (not walls), it returns 0
 * (no collision detected).
 * The function iterates through the indices i and j to sample
 * multiple points within the rectangle, allowing for a more
 * comprehensive collision check around the player's position.
 * @param map The map structure containing the grid and its dimensions.
 * @param r The floating-point rectangle representing the
 * player's collision area.
 * @param i The starting index for sampling (usually 0).
 * @return 1 if a collision is detected, 0 otherwise.
*/
int				frect_collides_map(t_map *map, const t_frect *r, int i);

/** 
 * main function for collision detection.
 * It takes the map, the player's position and the 
 * collision radius as input, converts the player's position
 * into a floating-point rectangle with the auxiliary function
 * and then checks for collisions with the map using the 
 * frect_collides_map function.
 * @param map The map structure containing the grid and its dimensions.
 * @param pos The player's position as a t_dcoord.
 * @param radius The collision radius around the player.
 * @return 1 if a collision is detected, 0 otherwise.
*/
int				rect_collides(t_map *map, t_dcoord pos, float radius);

/*----------------------- raycasting related functions ------------------ */

/**
 * function to perform the ray tracing process, 
 * which involves stepping through the grid using the DDA
 * algorithm to find the first wall hit by the ray.
 * 
 * The function first validates the input parameters to ensure they are
 * valid and initializes the DDA variables based on the ray's 
 * position and direction.
 * 
 * Then it calculates the initial side distances 
 * and enters a loop to find the first wall hit by stepping through
 * the grid.
 * 
 * If a wall is hit, it updates the ray's hit data with the
 * intersections details. If no wall is hit, it sets the ray's lenght
 * to 0 and the hit point to the ray's starting position.
 * 
 * This function also handles the case where the ray goes
 * out of bounds of the map, ensuring that the ray process does not
 * access invalid memory addresses and correctly handles edge cases.
 * 
 * @param ray The ray structure to trace.
 * @param map The minimap structure containing the grid and its dimensions.
 * @param hit_point Optional pointer to store the hit point coordinates.
 */
void			trace_ray(t_ray *ray, t_minimap *map, t_dcoord *hit_point);

/** 
 * function to draw a ray on the minimap.
 * It takes the ray structure, the minimap structure, and an optional
 * pointer to store the hit point coordinates.
 * 
 * The function calculates the start and end points of the ray on the minimap
 * based on the player's position and the hit point, applying the minimap's
 * scale and offset to convert from world coordinates to minimap coordinates.
 * 
 * It then uses a line drawing function (draw_line)
 * to render the ray on the minimap's buffer, using the ray's color
 * for the line.
 * 
 * The function also includes validation checks to ensure that the ray, minimap,
 * player, hit point, and ray data are all valid before
 * attempting to draw the ray,
 * preventing potential null pointer dereferences and ensuring that the drawing
 * operation is only performed when all necessary data is available.
 * @param ray The ray structure to draw.
 * @param map The minimap structure containing the grid and its dimensions.
 * @param hit_point Optional pointer to store the hit point coordinates.
 */
void			draw_ray_on_minimap(t_ray *ray, t_minimap *map,
					t_dcoord *hit_point);

/**
 * function to render a ray on the minimap.
 * 
 * It first validates the input parameters and then initializes
 * the ray using the player's current angle and minimap's buffer
 * as the target for drawing.
 * 
 * @param ray The ray structure to render.
 * @param map The minimap structure containing the grid and its dimensions.
 * @param hit_point Optional pointer to store the hit point coordinates.
 */
void			render_ray(t_ray *ray, t_minimap *map);

/**
 * function to render the first ray from the player's position.
 * 
 * It initializes the ray based on the player's current angle and 
 * the minimap's buffer, and then calls the render_ray function to
 * perform the ray tracing and drawing on the minimap.
 */
void			render_first_ray(t_player *player, t_minimap *map, t_ray *ray);

/**
 * function to draw the player's field of view (FOV) rays on the minimap.
 * It initializes two rays representing the left and right edges
 * of the player's FOV. 
 * 
 * The main purpose of this function is to visually represent the player's 
 * FOV on the minimap, and it is applied for debugging purposes.
 * @param player The player structure containing the player's
 * position and angle.
 * @param map The minimap structure containing the grid and its dimensions.
 * @param target The data structure representing the minimap's
 * buffer where the rays will be drawn
 */
void			draw_fov_rays(t_player *player, t_minimap *map,
					t_data *target);

/* -------------------DDA related functions ------------------- */

/**
 * The DDA (digital differential analyzer) is the heart of 
 * the raycasting engine. 
 * 
 * It is responsible for stepping 
 * through the grid of the map to find the point where the 
 * ray hits a wall. 
 * It works by calculating the distance to the next grid line 
 * in both x and y directions, and then stepping to the next grid
 * cell in the direction of the ray.
 * This is the initialization function. It takes the ray's direction 
 * and position, and calculates the initial values needed for 
 * perform the operations.
 * 
 * It calculates the ray direction (rd), the current integer 
 * coordinates of the ray in the map (rmap), and the distance
 * to the next grid line in both x and y directions (delta_dist).
 * The delta_dist values are calculated as the absolute value of 
 * the inverse of the ray direction components, which represent
 * how far the ray has to travel in the x or y direction to 
 * cross a grid line.
 * 
 * If the ray direction component is zero, 
 * it set the delta_dist to a very large value (1e-30, or infinity)
 * to avoid division by zero and ensure that the ray will step in the
 * other direction.
 * @param ray The ray structure containing the starting position and direction.
 * @param rd Output parameter to store the calculated ray direction.
 * @param rmap Output parameter to store the initial grid coordinates of the ray.
 * @param delta_dist Output parameter to store the calculated
 * delta distances for x and y directions.
*/
void			init_dda_variables(t_ray *ray, t_dcoord *rd, t_icoord *rmap,
					t_dcoord *delta_dist);

/**
 * function needed to calculate the initial side distances for the 
 * DDA algorithm. 
 * It determines how far the ray has to travel from its
 * starting position to the first grid line in both x and y directions.
 * It checks the direction of the ray (positive or negative) to 
 *determine the step direction (step.x and step.y) and calculates
 * the initial side distances (side_dist.x and side_dist.y) based 
 * on the ray's position relative to the next grid line. This setup
 * is crucial for the DDA algorithm to correctly step through the
 * grid and find the point of intersection with a wall.
 * @param dda The DDA structure containing the ray's direction, current
 * grid coordinates, and delta distances.
 * @param ray_pos The current position of the ray in floating-point coordinates.
*/	
void			calc_side_dist(t_dda *dda, t_dcoord ray_pos);

/**
 * function to check if the current grid coordinates of the ray (rmap)
 * are within the bounds of the map. 
 * It ensures the DDA algorithm does not
 * step outside the map's dimensions, which could lead to invalid memory
 * accesses or incorrect behavior. The function returns 0 if the ray's current
 * grid is out of bounds, and 1 if it is within the bounds.
 * @param dda The DDA structure containing the 
 * current grid coordinates of the ray (rmap).
 * @param map The minimap structure containing
 * the reference map and its dimensions.
*/
int				check_bounds(t_dda *dda, t_minimap *map);

/**
 * Updates the ray hit data based on the DDA results.
 * 
 * This function calculates the exact hit point where the ray intersects a wall
 * based on the DDA algorithm's results. It computes the perpendicular distance
 * from the ray's starting position to the hit point, updates the ray's hit
 * coordinates, the grid coordinates of the hit, the side of the wall hit, and
 * the direction of the ray step. If a hit point output parameter is provided,
 * it also stores the hit point coordinates in that parameter.
 * 
 * @param ray The ray structure to update.
 * @param dda The DDA structure containing the intersection data.
 * @param hit_point Optional pointer to store the hit point.
 */
void			update_ray_hit_data(t_ray *ray, t_dda *dda,
					t_dcoord *hit_point);

/**
 * Updates the ray step based on the DDA algorithm.
 * 
 * This function determines which grid line the ray will
 * cross next and updates the ray's position accordingly.
 * 
 * It compares the side distances in both x and y
 * directions to decide which axis to step along.
 * 
 * @param dda The DDA structure containing the intersection data.
 */
void			update_ray_step(t_dda *dda);

/* -------------------ray initialization functions ------------------- */

/**
 * function to initialize the z-buffer for the raycasting engine.
 * 
 * The z-buffer is an array that stores the perpendicular distance from the
 * camera to the wall for each column of the screen. This information is used
 * for depth calculations, such as the shading of walls, and perspective 
 * correction.
 * 
 * The z-buffer is essential for rendering a 3d scene correctly, as it allows
 * the engine to determine how far away each wall is and apply the appropriate 
 * shading and perspective effects based on that distance, creating a more 
 * accurate representation of a 3D environment on a 2D screen.
 * 
 * The function allocates memory for the z-buffer based on the
 * screen width and initializes all values to zero. It returns a pointer to the
 * initialized z-buffer array.
 * @param game The game structure containing the configuration
 * for screen dimensions.
 * @return A pointer to the initialized z-buffer array.
 */
float			*init_zbuffer(t_game *game);

/**
 * function to initialize a ray structure for casting rays in the 
 * raycasting engine.
 * It sets the ray's starting position to the player's position, calculates the
 * ray's direction based on the player's angle and the specified ray angle, 
 * and initiates other proprieties of the ray such as length, hit information 
 * and the target data for rendering.
 * 
 * This function is crucial for setting up the ray before it is cast 
 * into the scene, ensuring that the ray has the correct starting
 * position and direction based on the player's orientation
 * and the specific column of the screen it corresponds to.
 * @param ray The ray structure to initialize.
 * @param player The player structure containing the current position and angle.
 * @param ray_angle The angle of the ray to be cast, relative to
 * the player's angle
 * @param target The data structure representing the target for
 * rendering the ray's hit.
 */
void			init_ray(t_ray *ray, t_player *player, float ray_angle,
					t_data *target);

/**
 * function to initialize the column data structure for rendering
 * a single column of the screen based on the ray's perpendicular
 * distance to the wall and the screen height. 
 * 
 * It calculates the height of the wall slice to be drawn for
 * that column, the x-coordinate of the column on the screen, and stores the 
 * perpendicular distance and screen height for later use in 
 * rendering the column.
 * 
 * This function is needed to prepare the necessary data for rendering a
 * vertical slice of the wall corresponding to a specific column on the screen.
 */
void			init_column(t_column *col, int x, float perp, int screen_h);

/**
 * function to initialize the camera structure based on 
 * the player's position and orientation. 
 * 
 * It sets the camera's position to match the player's position,
 * and calculates the camera's direction and plane vectors based
 * on the player's angle relative to the world. 
 * 
 * The direction vector is calculated using the cosine and sine 
 * of the player's angle, while the plane vector is calculated by 
 * rotating the direction vector by 90 degrees and scaling 
 * it to determine the FOV.
 * 
 * This setup ensures that the camera's view is correctly
 * aligned with the player's orientation, allowing for a 
 * consistent first-person perspective following the rotation
 * and movement of the player within the game world.
 * 
 * @param camera The camera structure to initialize.
 * @param player The player structure containing 
 * the current position and angle.
 * 
 */
void			init_camera(t_camera *camera, t_player *player);

/* -----------------------camera related functions ----------------------- */

/**
 * function to rotate the camera by a given angle.
 * It calculates the new direction and plane vectors
 * using the standard 2D rotation formulas.
 * The direction vector is rotated by the specified angle,
 * and the plane vector is rotated by the same angle 
 * to mantain the correct FOV. This allows the camera to look
 * in a different direction by keeping the same position and FOV.
 * It uses the sine and cosine of the angle to perform the rotation,
 * and updates the camera's direction and plane following
 * the rotation formulas.
 * @param camera The camera structure to rotate.
 * @param angle The angle in radians to rotate the camera.
*/
void			rotate_camera(t_camera *camera, float angle);

/**
 * function to move the camera forward or backward based 
 * on its current direction and the specified movement step.
 * It calculates the new position by adding the movement step
 * multiplied by the direction vector for both x and y coordinates.
 * Before updating the camera's position, it checks for collisions
 * with walls using the rect_collides function. If there is no collision,
 * it updates the camera's position.
 * The movement step is applied in the direction the camera is facing,
 * allowing it to move forward or backward while checking for potential
 * collisions with the map's walls.
 * @param camera The camera structure to move.
 * @param map The map structure containing the grid and its dimensions.
 * @param move_step The distance to move the camera, where positive values
 * move forward and negative values move backward.
 */
void			move_camera(t_camera *camera, t_map *map, float move_step);

/**
 * function to calculate the ray direction for a specific column
 * on the screen based on the camera's direction and plane.
 * It calculates the camera_x coordinate,
 * which represents the position of the ray, relative to the 
 * center of screen. The camera_x value ranges from -1 to 1, where -1
 * corresponds to the left edge of the screen and 1 corresponds 
 * to the right edge. The ray direction is then calculated by
 * adding the camera's direction vector to the camera
 * plane vector multiplied by the camera_x coordinate. This
 * allows the ray to be cast in the correct direction based on
 * the camera's orientation and the position of the column 
 * on the screen. The function also initializes other ray properties
 * such as the starting position, length, and hit information.
 * @param camera The camera structure containing the direction and plane.
 * @param x The x-coordinate of the column on the screen
 * for which to calculate the ray
 * @param ray The ray structure to initialize with the calculated direction
 * and other properties.
*/
void			get_camera_ray(t_camera *camera, int x, t_ray *ray);

/**
 * function to update the camera's position and orientation
 * based on the player's current state.
 * It sets the camera's position to match the player's position,
 * and updates the camera's direction and plane vectors to align
 * with the player's angle. 
 * 
 * The direction vector is calculated using
 * the cosine and sine of the player's angle, while the plane vector
 * is calculated by rotating the direction vector by 90 degrees and
 * scaling it by a factor (0.66 in this case) to determine
 * the field of view. 
 * 
 * This function ensures that the camera's view
 * is always aligned with the player's orientation,
 * allowing for a consistent first-person perspective as the
 * player moves and rotates within the game world.
 * 
 * @param camera The camera structure to update.
 * @param player The player structure containing the current
 * position and angle.
 */
void			update_camera(t_camera *camera, t_player *player);

/* -------------------ray casting utilities ------------------- */

/**
 * function to validate the inputs for the ray projection process.
 * It checks if the ray, minimap, and hit_point pointers are not null,
 * and also checks if the ray's player and data pointers are valid.
 * 
 * This function is ensure the integrity of the data being used,
 * ensuring that there's no null pointer dereference during the 
 * following ray trace process. 
 * 
 * @param ray The ray structure to validate.
 * @param map The minimap structure to validate.
 * @param hit_point Optional pointer to store 
 * the hit point in case of invalid input.
 * @return 1 if the inputs are valid, 0 otherwise.
 */
int				validate_trace_inputs(t_ray *ray, t_minimap *map,
					t_dcoord *hit_point);

/**
 * function to calculate the perpendicular distance from the camera
 * to the wall hit by the ray. This distance is used for the correct
 * rendering of the wall slice corresponding to the ray, as it allows
 * for perspective correction and proper shading based on the distance
 * to the wall.
 * 
 * The way the perpendicular distance is calculated depends on which
 * side of the wall was hit (x or y). If the ray hit a vertical wall
 * (side 0), the distance is calculated using the x component of the
 * ray's position and direction. If the ray hit a horizontal wall (side 1),
 * the distance is calculated using the y component.
 * 
 * This function is needed to ensure that the rendered wall slices
 * are correctly scaled based on their distance from the camera, 
 * avoiding the fisheye effect and providing a right perspective
 * when rendering the 3D scene.
 *
 * @param ray The ray structure containing the hit information and direction.
 * @param cam_dir_u The unit vector of the camera's direction, used for
 * perspective correction.
 * @return The calculated perpendicular distance
 * from the camera to the wall hit.
 */
float			perp_dist_from_proj(const t_ray *ray,
					const t_dcoord cam_dir_u);

/**
 * function to compute the height of the wall slice to be drawn
 * for a specific column on the screen based on the perpendicular
 * distance to the wall and the screen height.
 * 
 * The line height is calculated as the ratio of the screen 
 * height to the perpendicular distance, which determines
 * how tall the wall slice should be rendered to create the correct
 * perspective effect. 
 * 
 * If the perpendicular distance is zero or negative (which can happen)
 * the function sets the line height to the screen height to avoid
 * division by zero and ensuring that the wall slice is rendered
 * at maximum height, which can be considered as fallback behavior in
 * case of invalid distance values.
 * 
 * the greater the perpendicular distance, the smaller the line height,
 * which creates the illusion of depth, making distant walls appear
 * shorter.
 * @param screen_h The height of the screen in pixels.
 * @param perp_dist The perpendicular distance from
 * the camera to the wall hit.
 */
int				compute_line_height(int screen_h, float perp_dist);

/**
 * function to clamp the drawing bounds for a wall slice on the screen.
 * 
 * It takes the calculated line height and the screen height, and 
 * determines the starting and ending y-coordinates for drawing the
 * wall slice.
 * 
 * The function ensures that the draw_start and draw_end values
 * are within the bounds of the screen, preventing any drawing outside
 * the visible area. 
 * 
 * If the calculated draw start is less than 0, it is set to 0, 
 * and the calculated draw end is set to the line height.
 * If the calculated draw end exceeds the screen height, it is set to
 * the screen height, and the draw start is adjusted accordingly
 * to maintain the correct line height.
 * @param line_h The calculated height of the wall slice to be drawn.
 * @param screen_h The height of the screen in pixels.
 * @param draw_start Output parameter to store the clamped
 * starting y-coordinate for drawing.
 * @param draw_end Output parameter to store the clamped
 * ending y-coordinate for drawing.
 */
void			clamp_draw_bounds(int line_h, int screen_h,
					int *draw_start, int *draw_end);

/**
 * function to get the appropriate texture for a wall hit based
 * on the direction of the ray and the side of the wall hit.
 * 
 * if the ray hit a vertical wall (side 0), it checks the x component
 * of the ray's direction to determine if it hit a north-facing or 
 * south-facing wall, and returns the corresponding texture.
 * 
 * if the ray hit a horizontal wall (side 1), it checks the y component
 * of the ray's direction to determine if the wall is 
 * east-facing or west-facing, and returns the corresponding texture.
 * 
 * @param game The game structure containing the textures 
 * for each wall direction.
 * @return A pointer to the texture image corresponding
 * to the wall hit.
 */
t_image			*get_directional_texture(t_game *game);

/* -------------------column related functions -------------------*/

/**
 * function to cast a single column of the screen by performing raycasting
 * for a specific x-coordinate.
 * 
 * It calculates the ray direction for the column, traces
 * the ray to find the wall hit, calculates the perpendicular distance
 * to the wall, initializes the column data for rendering, and then
 * renders the wall slice for that column based on the ray's hit information.
 * 
 * This function is called for each column on the screen to render 
 * the complete scene, and it encapsulates the entire process of raycasting
 * and rendering for a single vertical slice of the screen.
 * 
 * @param game The game structure containing the player, map, and textures.
 * @param data The data structure representing the target for rendering.
 * @param camera The camera structure containing the current
 * position and orientation.
 * @param x The x-coordinate of the column on the screen to cast.
 */
void			cast_single_column(t_game *game, t_data *data,
					t_camera *camera, int x);

/** 
 * function to get the color of a specific pixel in the wall texture
 * based on the ray's hit information and the column data.
 * 
 * This function is needed to determine the correct colors to render
 * each pixel of the wall slice for a specific column, taking into account
 * the texture mapping based on the hit point and the shading effects based
 * on the distance to the wall.
 * 
 * It calculates the texture coordinates based on the hit point and the
 * column data, retrieves the color from the texture at those coordinates,
 * and applies shading to the color based on the distance to the wall and
 * the side of the wall hit to create a more realistic rendering effect.
 * 
 * @param game The game structure containing the textures
 * and shading parameters.
 * @param col The column data structure.
 * @param tex The texture image.
 * @param y The y-coordinate of the pixel to retrieve.
 * @return The color of the specified pixel.
 */
unsigned int	get_column_color(t_game *game, t_column *col,
					t_image *tex, int y);

/**
 * function to draw the pixels of a wall column on the screen, 
 * based on the column data and the corresponding texture.
 * 
 * It takes into account the shading effects, the texture mapping and 
 * the distance to the wall to render the correct colors for each pixel
 * of the wall slice for a specific column on the screen.
 * 
 * @param game The game structure containing the textures and shading parameters.
 * @param data The data structure representing the target for rendering.
 * @param col The column data structure containing the information
 * for rendering the column.
 * @param tex The texture image to use for rendering the wall slice.
 */
void			draw_column_pixels(t_game *game, t_data *data, t_column *col,
					t_image *tex);

/**
 * function to render a wall column on the screen, 
 * based on the column data and the corresponding texture.
 * 
 * It takes into account the shading effects, the texture mapping and 
 * the distance to the wall to render the correct colors for each pixel
 * of the wall slice for a specific column on the screen.
 * 
 * the function is responsible for drawing the vertical
 * slice of the wall corresponding to a specific column on the screen,
 * using the ray's hit information and the angle of the ray 
 * to determine the correct texture and shading for the wall slice, 
 * and then calling the draw_column_pixels function for rendering.
 * 
 * @param game The game structure containing the textures and shading parameters.
 * @param data The data structure representing the target for rendering.
 * @param x The x-coordinate of the column on the screen to render.
 * @param perp The perpendicular distance to the wall.
 */
void			render_wall_column(t_game *game, t_data *data, int x,
					float perp);

/* -------------------color related functions -------------------*/

/**
 * function to convert a t_color structure to a hexadecimal color value.
 * It takes the red, green, and blue components of the t_color structure,
 * and combines them into a single unsigned integer in the format 0xRRGGBB
 * (where RR is the red component, GG is the green component, and BB is the blue
 * component).
 * 
 * This allows for easy use of the color in rendering functions
 * that require a single integer representation of the color.
 * 
 * @param color The t_color structure containing the red,
 * green, and blue components.
 * @return The hexadecimal color value as an unsigned integer.
 */
unsigned int	color_to_hex(t_color color);

/**
 * function to convert a hexadecimal color value to a t_color structure.
 * It takes an unsigned integer representing a color in the format 0xRRGGBB
 * and extracts the red, green, and blue components to populate a
 * t_color structure.
 * 
 * the struct is useful for manipulating individual color components, 
 * such as applying shading or darkening effects, before converting it 
 * back to a hexadecimal value for rendering.
 * @param hex The hexadecimal color value as an unsigned integer.
 * @return A t_color structure containing separated
 * red, green, and blue components.
 */
t_color			hex_to_color(unsigned int hex);

/**
 * function to apply shading to a color based on a shade factor.
 * It takes a t_color structure and a shade factor
 * (a float between 0 and 1), and returns a new t_color structure
 * with the red, green, and blue components
 * scaled by the shade factor.
 * 
 * A shade factor of 1 means no shading (full brightness), 
 * while a shade factor of 0 means full shading (black).
 * Values between 0 and 1 will darken the color proportionally,
 * creating a shading effect based on the distance
 * to the wall or other factors in the scene.
 * @param color The original t_color structure to be shaded.
 * @param shade The shade factor to apply, where 1 is no shading and 0
 * is full shading.
 * @return A new t_color structure with the applied shading.
 */
t_color			apply_shade(t_color color, float shade);

/**
 * function to apply darkening to a color based on the
 * side of the wall hit.
 * It takes a t_color structure and an integer
 * representing the side of the wall hit.
 * 
 * It's an auxiliary function to apply a darkening effect to the color
 * based on the side of the wall hit, which can be used to create
 * a visual distinction between different sides of the walls, enhancing
 * the illusion of depth and lighting in the rendered scene.
 * 
 * @param color The original t_color structure to be darkened.
 * @param side The side of the wall hit (0 for vertical walls,
 * 1 for horizontal walls).
 * @return A new t_color structure with the applied darkening effect.
 */
t_color			apply_side_darkening(t_color color, int side);

/**
 * function to calculate the shade factor based on the distance 
 * to the wall, a shadow coefficient and the light intensity.
 * 
 * It takes the distance from the camera to the wall, 
 * a shadow coefficient that determines how quickly the
 * shade factor decreases with distance, and the light intensity
 * which can be used to adjust the overall brightness of the scene.
 * 
 * this function is needed to create a shading effect that simulates
 * the way light diminishes with distance, allowing for a more
 * accurate representation of depth and lighting in 
 * the rendered scene. 
 * 
 * The shade factor is calculated using an exponential decay formula, 
 * where the distance is multiplied by the shadow coefficient to
 * determinate how much the shade factor decreases as the distance
 * increases, an then multiplied by the light intensity to 
 * adjust the overall brightness of the shading effect.
 * @param distance The distance from the camera to the wall hit.
 * @param shadow_k The shadow coefficient that determines
 * how quickly the shade factor decreases whith the distance.
 * (this value can be adjusted to achieve different shading effects).
 * @param light_intensity The overall light intensity to adjust
 * the brightness of the shading effect (1 for normal brightness
 * and values less than 1 for darker scenes).
 * @return The calculated shade factor to be applied to the color.
 */
float			calculate_shade_factor(float distance, float shadow_k,
					float light_intensity);

#endif