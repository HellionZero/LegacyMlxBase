/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:35:12 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/20 15:16:24 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCTS_H
# define CUB_STRUCTS_H

typedef struct s_window	t_window;
typedef struct s_game	t_game;
typedef struct s_data	t_data;
typedef struct s_icoord	t_icoord;
typedef struct s_dim	t_dim;

/*
img: pointer to the image created by mlx_new_image
tmp_img: pointer to a temporary image used for off-screen rendering
addr: pointer to the memory area where the image
data can be accessed
bits_per_pixel: number of bits used to
represent each pixel in the image
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

/*
mlx_ptr: pointer to the MLX instance, 
used for all MLX operations
win_ptr: pointer to the window created by MLX,
used for rendering and event handling
*/
struct s_icoord
{
	int	x;
	int	y;
};

struct s_dim
{
	int	width;
	int	height;
};

struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	*img_ptr;
};

struct s_game
{
	t_window	*window;
};

#endif