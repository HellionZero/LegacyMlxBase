/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:32:26 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/09 19:38:31 by bmoreira         ###   ########.fr       */
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
	game->map = NULL;
	game->minimap = NULL;
	game->ray.data = NULL;
	game->z_buffer = NULL;
	game->config.fog_distance = 20.0f;
	game->config.light_intensity = 1.0f;
	game->config.shadow_factor = 0.1f;
	game->config.max_render_distance = 100;
	game->config.render_quality = 1;
	ft_bzero(&game->input, sizeof(t_input));
	ft_bzero(&game->player_rect, sizeof(t_frect));
	ft_bzero(&game->ray, sizeof(t_ray));
}

void	init_game(t_game *game, char **argv)
{
	if (!game || !argv || !argv[1])
		return ;
	game->window = create_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!game->window)
		alert_and_exit("Failed to create window\n", game);
	init_null_defaults(game);
	game->map = init_map();
	if (!game->map)
		alert_and_exit("Failed to initialize map\n", game);
	if (parse_map(game->map, argv[1]) != 0)
		alert_and_exit("Failed to parse map\n", game);
	init_timer(&game->timer);
	load_map_textures(game);
	game->ray.data = game->window->img_ptr;
	game->minimap = create_minimap(game);
	if (!game->minimap)
		alert_and_exit("Failed to create minimap\n", game);
	game->z_buffer = init_zbuffer(game);
	if (!game->z_buffer)
		alert_and_exit("Failed to create z-buffer\n", game);
}
