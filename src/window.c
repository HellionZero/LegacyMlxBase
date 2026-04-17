/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:25:44 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/17 16:40:59 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

t_window	*create_window(int width, int height, char *title)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	if (!window)
	{
		fprintf(stderr, "Failed to create window\n");
		return (NULL);
	}
	window->mlx_ptr = mlx_init();
	if (!window->mlx_ptr)
	{
		fprintf(stderr, "Failed to initialize MLX\n");
		free(window);
		return (NULL);
	}
	window->win_ptr = mlx_new_window(window->mlx_ptr, width, height, title);
	if (!window->win_ptr)
	{
		fprintf(stderr, "Failed to create window\n");
		free(window->mlx_ptr);
		free(window);
		return (NULL);
	}
	return (window);
}
