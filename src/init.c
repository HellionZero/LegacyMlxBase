/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:32:26 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/29 18:12:31 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	alert_and_exit(char *message, t_game *game)
{
	ft_putstr_fd(message, 2);
	free_game(game);
	exit(1);
}

static void	init_null_defaults(t_game *game)
{
	game->wall_texture = NULL;
	game->floor_texture = NULL;
	game->ceiling_texture = NULL;
	game->map = NULL;
	game->player = NULL;
	game->minimap = NULL;
	game->ray.data = NULL;
}

void	init_game(t_game *game)
{
	if (!game)
		return ;
	game->window = create_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!game->window)
		alert_and_exit("Failed to create window\n", game);
	fprintf(stderr, "init_game: start\n");
	init_null_defaults(game);
	init_timer(&game->timer);
	fprintf(stderr, "init_game: creating player\n");
	game->player = create_player();
	if (!game->player)
		alert_and_exit("Failed to create player\n", game);
	fprintf(stderr, "init_game: init_map\n");
	init_map(game);
	fprintf(stderr, "init_game: setting ray.data\n");
	game->ray.data = game->window->img_ptr;
	fprintf(stderr, "init_game: creating minimap\n");
	game->minimap = create_minimap(game);
	if (!game->minimap)
		alert_and_exit("Failed to create minimap\n", game);
}
