/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:23:00 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/07 18:05:48 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_TYPES_H
# define CUB_TYPES_H

# define BLUE 0x0000FF
# define GREEN 0x00FF00
# define RED 0xFF0000
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

# define PI 3.14159265358979323846

# define ROT_FACTOR 2.0f
# define STEP_SIZE 0.1f

typedef enum e_points		t_points;
typedef enum e_sides		t_sides;
typedef struct s_dim		t_dim;
typedef struct s_icoord		t_icoord;
typedef struct s_dcoord		t_dcoord;
typedef struct s_fcoord		t_fcoord;
typedef struct s_color		t_color;
typedef struct s_point		t_point;

/*e_points: enumeration to represent the main
nine points of a rectangle. 
subject to future implementation */
enum e_points
{
	TOP_LEFT,
	TOP_CENTER,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_CENTER,
	BOTTOM_RIGHT,
	CENTER_LEFT,
	CENTER_RIGHT,
	CENTER
};

/*e_sides: enumeration to represent the four sides of a rectangle */
enum e_sides
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

/*s_icoord: structure to represent integer coordinates */
struct s_icoord
{
	int	x;
	int	y;
};

/*s_dcoord: structure to represent double coordinates */
struct s_dcoord
{
	double	x;
	double	y;
};

/*s_fcoord: structure to represent float coordinates */
struct s_fcoord
{
	float	x;
	float	y;
};

/*s_point: structure to represent a point */
struct s_point
{
	int	start;
	int	end;
};

/*s_dim: structure to represent dimensions */
struct s_dim
{
	int	width;
	int	height;
};

/*s_color: structure to represent a color, 
utilizing RGB values. all values of the variables
can be manipulated with bitwise operations */
struct s_color
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
};

#endif