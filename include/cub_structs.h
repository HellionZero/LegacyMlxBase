/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:35:12 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/04 17:05:40 by lsarraci         ###   ########.fr       */
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
typedef struct s_sprite		t_sprite;
typedef struct s_image		t_image;
typedef struct s_timer		t_timer;
typedef struct s_input		t_input;

/*
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

struct s_line
{
	t_icoord	start;
	t_icoord	end;
	int			color;
};

/*
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

struct s_image
{
	void	*img_ptr;
	char	*path;
	char	*addr;
	t_data	data;
	t_dim	dim;
};

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

struct s_column
{
	int			x;
	int			line_h;
	float		perp;
	int			tex_x;
	int			screen_h;
};

struct s_wall_ctx
{
	double	wall_x;
	t_image	*texture;
	int		tex_x;
	int		hit_side;
};

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
	int			hit_side; /* 0 = vertical (x), 1 = horizontal (y) */
	int			color;
};

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

struct s_rectangle
{
	t_icoord	pos;
	t_dim		dim;
	int			color;
	t_icoord	points[9];
};

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

struct s_sprite
{
	t_icoord	pos;
	t_dim		dim;
	t_image		*texture;
	int			color;
	int			rotation;
};

/*
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
	t_image			*wall_texture;
	t_image			*floor_texture;
	t_image			*ceiling_texture;
	t_minimap		*minimap;
	float			*z_buffer;
};

#endif