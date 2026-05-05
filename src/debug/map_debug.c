/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:01:40 by lsarraci          #+#    +#+        */
/*   Updated: 2026/04/28 18:34:35 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

t_map	temp_map(void)
{
	static char	*grid[] = {
		"   11111   ",
		"11110001111",
		"10000000001",
		"1011000S001",
		"10000100001",
		"11111111111"
	};
	t_map		map;

	map.ceiling_color = 0x87CEEB;
	map.floor_color = 0x228B22;
	map.grid = grid;
	map.dim.width = count_map_columns(grid);
	map.dim.height = count_map_rows(grid);
	map.north_path = "src/assets/img_xpm/north_texture.xpm";
	map.south_path = "src/assets/img_xpm/south_texture.xpm";
	map.west_path = "src/assets/img_xpm/west_texture.xpm";
	map.east_path = "src/assets/img_xpm/east_texture.xpm";
	map.north_texture = NULL;
	map.south_texture = NULL;
	map.west_texture = NULL;
	map.east_texture = NULL;
	return (map);
}


