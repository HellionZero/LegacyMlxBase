/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:23:43 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/20 14:51:42 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	mlx_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	mlx_remove_pixel(t_data *data, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = 0;
}

void	clear_buffer(t_data *data, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			mlx_put_pixel(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_frame(t_data *data, void *mlx_ptr, void *win_ptr)
{
	if (!data || !data->img)
		return ;
	mlx_put_image_to_window(mlx_ptr, win_ptr, data->img, 0, 0);
}

void	free_pixel_data(t_data *data, void *mlx_ptr)
{
	if (!data)
		return ;
	if (data->img)
		mlx_destroy_image(mlx_ptr, data->img);
	if (data->tmp_img)
		mlx_destroy_image(mlx_ptr, data->tmp_img);
	free(data);
}
