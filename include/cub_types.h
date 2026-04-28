/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:23:00 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/28 16:43:36 by lsarraci         ###   ########.fr       */
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

typedef enum e_points		t_points;
typedef enum e_sides		t_sides;
typedef struct s_dim		t_dim;
typedef struct s_icoord		t_icoord;
typedef struct s_dcoord		t_dcoord;

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

enum e_sides
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

struct s_icoord
{
	int	x;
	int	y;
};

struct s_dcoord
{
	double	x;
	double	y;
};

struct s_dim
{
	int	width;
	int	height;
};

#endif