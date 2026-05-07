/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:08:39 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/07 17:34:52 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3D <path_to_map.cub>\n", 2);
		return (1);
	}
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		ft_putstr_fd("Failed to allocate memory for game\n", 2);
		return (1);
	}
	init_game(game, argv);
	setup_hooks(game);
	mlx_loop(game->window->mlx_ptr);
	return (0);
}
