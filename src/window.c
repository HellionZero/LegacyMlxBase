/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:25:44 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/20 15:00:13 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static t_data	*prepare_image_data(void *mlx_ptr, int width, int height)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->width = width;
	data->height = height;
	data->img = mlx_new_image(mlx_ptr, width, height);
	if (!data->img)
	{
		free(data);
		return (NULL);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (!data->addr)
	{
		mlx_destroy_image(mlx_ptr, data->img);
		free(data);
		return (NULL);
	}
	data->tmp_img = NULL;
	return (data);
}

void	initialize_image_data(t_window *window, int width, int height)
{
	if (!window || !window->mlx_ptr)
		return ;
	window->img_ptr = prepare_image_data(window->mlx_ptr, width, height);
	if (!window->img_ptr)
	{
		ft_putstr_fd("Failed to initialize image data\n", 2);
		mlx_destroy_window(window->mlx_ptr, window->win_ptr);
		mlx_destroy_display(window->mlx_ptr);
		free(window->mlx_ptr);
		free(window);
		return ;
	}
}

void	initialize_window_data(t_window *window, int width,
			int height, char *title)
{
	if (!window)
		return ;
	window->mlx_ptr = mlx_init();
	if (!window->mlx_ptr)
	{
		ft_putstr_fd("Failed to initialize MLX\n", 2);
		free(window);
		return ;
	}
	window->win_ptr = mlx_new_window(window->mlx_ptr, width, height, title);
	if (!window->win_ptr)
	{
		ft_putstr_fd("Failed to create window\n", 2);
		mlx_destroy_display(window->mlx_ptr);
		free(window->mlx_ptr);
		free(window);
		return ;
	}
	initialize_image_data(window, width, height);
}

t_window	*create_window(int width, int height, char *title)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	if (!window)
	{
		ft_putstr_fd("Failed to create window\n", 2);
		return (NULL);
	}
	initialize_window_data(window, width, height, title);
	if (!window->img_ptr || !window->win_ptr)
	{
		ft_putstr_fd("Failed to initialize window properly\n", 2);
		free(window);
		return (NULL);
	}
	return (window);
}
