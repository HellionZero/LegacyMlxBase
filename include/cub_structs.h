/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:35:12 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/07 16:48:20 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCTS_H
# define CUB_STRUCTS_H

# include "cub_types.h"

typedef struct s_render_cfg	t_render_cfg;
typedef struct s_window		t_window;
typedef struct s_game		t_game;
typedef struct s_map		t_map;
typedef struct s_minimap	t_minimap;
typedef struct s_player		t_player;
typedef struct s_camera		t_camera;
typedef struct s_column		t_column;
typedef struct s_wall_ctx	t_wall_ctx;
typedef struct s_ray		t_ray;
typedef struct s_dda		t_dda;
typedef struct s_wall		t_wall;
typedef struct s_illum		t_illum;
typedef struct s_data		t_data;
typedef struct s_line		t_line;
typedef struct s_frect		t_frect;
typedef struct s_rectangle	t_rectangle;
typedef struct s_image		t_image;
typedef struct s_timer		t_timer;
typedef struct s_input		t_input;

/*
s_data: structure that holds the image data and dimensions for rendering.
each image inside minilibx is represented by a t_data struct,
which contains the following fields:

img: pointer to the image created by mlx_new_image
tmp_img: pointer to a temporary image used for
off-screen rendering
addr: pointer to the memory area where the image data
can be accessed
bits_per_pixel: number of bits used to represent
each pixel in the image
line_length: number of bytes in a single row of the image
endian: indicates the endianness of the image data
(0 for little-endian, 1 for big-endian)
width: width of the image in pixels
height: height of the image in pixels
*/
struct s_data
{
	void	*img;
	void	*tmp_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
};

/*s_line: structure that holds the start and end points of a line,
along with its color for rendering. it's an important function, 
responsible to draw the rays in the minimap.
it utilizes Bresenham's line algorithm to efficiently
draw a line between two points on the screen.
the algorithm calculates the difference in x and y
coordinates between the start and end points,
and determines the steps needed to draw the line while
minimizing the number of pixels used.

fields:
start: the starting point of the line, represented as a t_icoord structure
end: the ending point of the line, represented as a t_icoord structure
color: the color of the line, represented as an integer 
(usually in hexadecimal format)
*/
struct s_line
{
	t_icoord	start;
	t_icoord	end;
	int			color;
};

/*
s_timer: structure that holds timing information for the game,
used to calculate the time difference between frames and
control the game's timing and animation.
It contains the following fields:

timeval: structure that holds the last recorded time
and the delta time between frames
last_time: the last recorded time, used to calculate
the time difference between frames
delta_time: the time difference between the current
frame and the last recorded time,
used for timing and animation purposes
*/
struct s_timer
{
	struct timeval	last_time;
	float			delta_time;
};

/*s_input: structure that holds the input state for the game,
used to handle keyboard and mouse input events.
It contains the following fields:

left: boolean indicating if the left arrow key is pressed
right: boolean indicating if the right arrow key is pressed
up: boolean indicating if the up arrow key is pressed
down: boolean indicating if the down arrow key is pressed
w: boolean indicating if the 'W' key is pressed
a: boolean indicating if the 'A' key is pressed
s: boolean indicating if the 'S' key is pressed
d: boolean indicating if the 'D' key is pressed
*/
struct s_input
{
	int	left;
	int	right;
	int	up;
	int	down;
	int	w;
	int	a;
	int	s;
	int	d;
};

/*s_image: structure that holds the image data and dimensions for rendering.
It contains the following fields:

img_ptr: pointer to the image created by mlx_new_image
path: the file path to the image, used for loading textures
addr: pointer to the memory area where the image data can be accessed
data: structure that holds the image data and dimensions
dim: structure that holds the width and height of the image
*/
struct s_image
{
	void	*img_ptr;
	char	*path;
	char	*addr;
	t_data	data;
	t_dim	dim;
};

/*s_render_cfg: structure that holds the rendering configuration for the game,
used to control various rendering parameters and effects. 

fields:
fog_distance: the distance at which fog starts to affect the rendering
ray_distance: the distance at which rays are rendered
light_intensity: the intensity of the light in the scene
shadow_factor: the factor that controls the darkness of shadows
shade: the overall shade applied to the scene
shadow_k: the factor that controls the darkness of shadows based on distance
max_render_distance: the maximum distance at which objects are rendered
render_quality: the quality level of rendering, which can affect performance
base_color: the base color used for rendering
shade_color: the color used for shading effects
tex_color: the color used for textures
shaded_hex: the final color value after applying shading and lighting effects,
represented as an unsigned integer (usually in hexadecimal format)
*/
struct s_render_cfg
{
	float			fog_distance;
	float			ray_distance;
	float			light_intensity;
	float			shadow_factor;
	float			shade;
	float			shadow_k;
	int				max_render_distance;
	int				render_quality;
	t_color			base_color;
	t_color			shade_color;
	t_color			tex_color;
	unsigned int	shaded_hex;
};

/*s_column: structure that holds the column data for rendering. 
fields:

x: the x-coordinate of the column on the screen
line_h: the height of the line to be drawn for the column
perp: the perpendicular distance from the camera to the wall hit by the ray
tex_x: the x-coordinate on the texture that corresponds to the column
screen_h: the height of the screen, used for calculating
the line height and draw bounds
*/
struct s_column
{
	int			x;
	int			line_h;
	float		perp;
	int			tex_x;
	int			screen_h;
};

/*s_wall_ctx: structure that holds the context for wall rendering.
fields:
wall_x: the x-coordinate of the wall hit by the ray
texture: pointer to the texture image for the wall
tex_x: the x-coordinate on the texture that corresponds to the wall	
hit_side: the side of the wall that was hit by the ray
(0 for north/south, 1 for east/west). if any of the sides are hit, 
it verifies which side was hit */
struct s_wall_ctx
{
	double	wall_x;
	t_image	*texture;
	int		tex_x;
	int		hit_side;
};

/*s_map: main structure of the map data. it receives the 
dimensions, textures, and other map-related information.

fields:
north_texture: pointer to the texture image for the north wall
south_texture: pointer to the texture image for the south wall
west_texture: pointer to the texture image for the west wall
east_texture: pointer to the texture image for the east wall
north_path: the file path to the texture for the north wall
south_path: the file path to the texture for the south wall
west_path: the file path to the texture for the west wall
east_path: the file path to the texture for the east wall
grid: a 2D array of characters representing the map layout
dim: structure that holds the width and height of the map
floor_color: the color used for the floor,
represented as an unsigned integer
ceiling_color: the color used for the ceiling,
represented as an unsigned integer
*/
struct s_map
{
	t_image			*north_texture;
	t_image			*south_texture;
	t_image			*west_texture;
	t_image			*east_texture;
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	char			**grid;
	t_dim			dim;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
};

/*s_ray: main structure which holds the raycasting data.

fields:
t_data: structure that holds the image data and dimensions for rendering
player: pointer to the player structure, used to access the player's
position, direction and other attributes
pos: the integer coordinates of the ray's current position in the map grid
dir: the integer direction vector of the ray, used for DDA calculations
fpos: the floating-point coordinates of the ray's current position in the map
(needed for accurate raycasting calculations)
fdir: the floating-point direction vector of the ray
(needed for accurate raycasting calculations)
hit: the floating-point coordinates of the point where the ray hits a wall
(needed for the rendering of the wall slice)
length: the distance from the player to the point where the ray hits a wall
(determined by the DDA algorithm)
hit_wall: boolean indicating if the ray has hit a wall
hit_sprite: boolean indicating if the ray has hit a sprite
(may be used for future sprite rendering)
hit_side: the side of the wall that was hit by the ray
(0 for north/south, 1 for east/west)
color: the color of the ray, used for rendering the ray on the minimap
(and for debugging purposes)
*/
struct s_ray
{
	t_data		*data;
	t_player	*player;
	t_icoord	pos;
	t_icoord	dir;
	t_dcoord	fpos;
	t_dcoord	fdir;
	t_dcoord	hit;
	float		length;
	int			hit_wall;
	int			hit_sprite;
	int			hit_side;
	int			color;
};

/*s_dda: structure that holds the data for the DDA algorithm.
DDA (Digital Differential Analyzer) is a method used in raycasting to determine
the point of intersection between a ray and the walls in the map.
it utilizes the ray's position and direction
to step through the grid and find the point
where the ray hits a wall. it has advantages over other methods mainly 
in terms of performance and accuracy, as it allows for efficient traversal
of the grid and precise calculation of the intersection point.
the way the DDA algorithm works is by calculating the distance 
from the ray's current position
to the next grid line in both the x and y directions,
and then stepping to the next grid cell based on which distance is shorter.
this process continues until a wall is hit, at which point
the algorithm can determine the exact point
of intersection and the distance from the player to that point,
which is crucial for rendering the scene correctly.
the step size is determined by the ray's direction,
and the algorithm keeps track of the current
map cell the ray is in, as well as the distance
to the next grid line in both directions.

fields:
rmap: 		the integer coordinates of the ray's current position in the map grid
rd: 		the floating-point direction vector of the ray
delta_dist: the distance between the ray's
			current position and the next grid line
side_dist: 	the distance from the ray's current position to the next grid line
step: 		the step size in the x and y directions,
			determined by the ray's direction
*/
struct s_dda
{
	t_icoord	rmap;
	t_dcoord	rd;
	t_dcoord	delta_dist;
	t_dcoord	side_dist;
	t_icoord	step;
	int			hit;
	int			side;
};

struct s_camera
{
	t_dcoord	pos;
	t_dcoord	dir;
	t_dcoord	plane;
	t_icoord	screen_dim;
	float		inv_screen_width;
};

struct s_player
{
	t_dcoord	pos;
	t_dim		dim;
	int			color;
	t_ray		ray;
	float		angle;
	float		collision_radius;
	char		orientation;
};

/*
s_minimap: structure that holds the data for the minimap layer.
the minimap is a smaller representation of the game map, used to provide
the player with a visual overview of their surroundings. 
in this implementation, the minimap is rendered in a different buffer
than the main game view, allowing for efficient rendering and compositing,
and all the engine functions takes the minimap structure as a parameter.

it contains the following fields:
buffer: structure that holds the minimap's image data and dimensions
mlx_ptr: pointer to the MLX instance, used for all MLX operations
dim: dimensions of the minimap
ref_map: reference to the main game map, used to determine what to render
pos: position of the minimap on the screen
offset: offset to center the minimap around the player
player_pos: current position of the player, used to calculate 
	the player's position on the minimap
scale: scaling factor to adjust the size of the minimap
*/
struct s_minimap
{
	t_data		*buffer;
	void		*mlx_ptr;
	t_dim		dim;
	t_map		*ref_map;
	t_icoord	pos;
	t_icoord	offset;
	t_icoord	player_pos;
	float		scale;
};

/*s_rectangle: structure that holds the data for a rectangle shape.
its main use is for render the floor and ceiling of the renderer, 
as well of the walls in the minimap. 

fields:
pos:	position of the rectangle
dim		dimensions of the rectangle
color:	color of the rectangle
points: array of points that represent the corners of the rectangle,
		may be used for rotation and scaling transformations in the future.
*/
struct s_rectangle
{
	t_icoord	pos;
	t_dim		dim;
	int			color;
	t_icoord	points[9];
};

/*s_frect: structure that holds the data for a floating-point rectangle shape.
its main use is for collision detection. 

fields:
x: the x-coordinate of the rectangle's position
y: the y-coordinate of the rectangle's position
pos: the integer coordinates of the rectangle's position,
used for grid-based collision detection
dim: the dimensions of the rectangle
width: the width of the rectangle
height: the height of the rectangle
points: array of points that represent the corners and 
points of rotation of the rectangle.
may be used for collision detection and future transformations.
*/
struct s_frect
{
	float		x;
	float		y;
	t_dcoord	pos;
	t_dim		dim;
	float		width;
	float		height;
	int			points[9];
};

/*
s_window: structure that holds the data for the game window.
it contains the following fields:

mlx_ptr: pointer to the MLX instance, 
used for all MLX operations
win_ptr: pointer to the window created by MLX,
used for rendering and event handling
*/
struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	*img_ptr;
};

/*
s_game: main structure that holds all the game data and state.
fields:

window:		pointer to the game window structure,
			used for rendering and event handling
timer: 		structure that holds timing information for the game,
			used for the control the game's timing.
input:		structure that holds the input state for the game,
			used for the handling of keyboard input events.
player:		pointer to the player structure, used to access the
			player's position, direction and other attributes.
player_rect: structure that holds the data for the player's collision rectangle,
			used for collision detection.
map: 		pointer to the map structure, used to access the map layout,
			textures and other map-related information.
ray:		structure that holds the raycasting data, used for rendering 
			the scene and handling raycasting calculations.
config:		structure that holds the rendering configuration for the game, used
			for the control various rendering parameters and effects.
minimap:	pointer to the minimap structure, used for rendering the 
			minimap layer and providing the player with a visual
			overview of their surroundings.
map_file:	the file path to the map file, used for loading the map data
z_buffer:	pointer to an array of floats used for depth
			buffering in the raycasting rendering process,
			used to store the distance from the player to the walls
			for each column of the screen, allowing for correct rendering
			of walls based on their distance from the player and handling
			of occlusion and shading effects.
*/
struct s_game
{
	t_window		*window;
	t_timer			timer;
	t_input			input;
	t_player		*player;
	t_frect			player_rect;
	t_map			*map;
	t_ray			ray;
	t_render_cfg	config;
	t_minimap		*minimap;
	char			*map_file;
	float			*z_buffer;
};

#endif