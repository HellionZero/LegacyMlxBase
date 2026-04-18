/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 17:52:43 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/18 16:07:58 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

/* global variables*/
void	*g_mlx;
void	*win1;
void	*win2;

int	gere_mouse(int x, int y, int button, void *toto)
{
	printf("Mouse event - new win\n");
	mlx_destroy_window(g_mlx, win1);
	win1 = mlx_new_window(g_mlx, random() % 500, random() % 500, "new win");
	mlx_mouse_hook(win1, gere_mouse, 0);
	return (0);
}

int	main(void)
{
	srandom(time(0));
	g_mlx = mlx_init();
	win1 = mlx_new_window(g_mlx, 300, 300, "win1");
	win2 = mlx_new_window(g_mlx, 600, 600, "win2");
	mlx_mouse_hook(win1, gere_mouse, 0);
	mlx_mouse_hook(win2, gere_mouse, 0);
	mlx_loop(g_mlx);
}
