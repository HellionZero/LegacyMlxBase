/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:23:43 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/18 17:56:48 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	mlx_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void mlx_remove_pixel(t_data *data, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = 0;
	if (data->tmp_img)
	{
		char *tmp_dst = data->tmp_img + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)tmp_dst = 0;
	}
}

void free_pixel_data(t_data *data, void *mlx_ptr)
{
	if (data->img)
		mlx_destroy_image(mlx_ptr, data->img);
	if (data->tmp_img)
		mlx_destroy_image(mlx_ptr, data->tmp_img);
}
