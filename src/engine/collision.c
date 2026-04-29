/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:13:21 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/29 18:29:08 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/*t_frect	*player_to_rect(t_dcoord pos, t_dim dim)
{
	t_frect	*rect;

	rect = malloc(sizeof(t_frect));
	if (!rect)
		return (NULL);
	rect->x = pos.x - ((double)dim.width / 2.0);
	rect->y = pos.y - ((double)dim.height / 2.0);
	rect->width = dim.width;
	rect->height = dim.height;
	return (rect);
}*/

int	rect_collides(t_map *map, t_dcoord pos, t_dim dim)
{
	double	minx, miny, maxx, maxy;
	int		i_min, i_max, j_min, j_max;
	int		x, y;
	double	epsilon = 1e-6;

	if (!map || !map->grid)
		return (1);
	/* interpret pos as center of rectangle */
	minx = pos.x - ((double)dim.width / 2.0);
	miny = pos.y - ((double)dim.height / 2.0);
	maxx = pos.x + ((double)dim.width / 2.0);
	maxy = pos.y + ((double)dim.height / 2.0);
	i_min = (int)(minx);
	i_max = (int)(maxx - epsilon);
	j_min = (int)(miny);
	j_max = (int)(maxy - epsilon);
	if (i_min < 0 || j_min < 0 || i_max >= map->dim.width || j_max >= map->dim.height)
		return (1);
	x = i_min;
	while (x <= i_max)
	{
		y = j_min;
		while (y <= j_max)
		{
			if (map->grid[y][x] == '1')
			{
				fprintf(stderr, "rect_collides: collision at cell (%d,%d)\n", x, y);
				return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}
