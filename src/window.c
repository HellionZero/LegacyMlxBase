/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:25:44 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/18 17:21:47 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

t_window	*create_window(int width, int height, char *title)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	if (!window)
	{
		ft_putstr_fd("Failed to create window\n", 2);
		return (NULL);
	}
	window->mlx_ptr = mlx_init();
	if (!window->mlx_ptr)
	{
		ft_putstr_fd("Failed to initialize MLX\n", 2);
		free(window);
		return (NULL);
	}
	window->win_ptr = mlx_new_window(window->mlx_ptr, width, height, title);
	if (!window->win_ptr)
	{
		ft_putstr_fd("Failed to create window\n", 2);
		mlx_destroy_display(window->mlx_ptr);
		free(window->mlx_ptr);
		free(window);
		return (NULL);
	}
	return (window);
}
