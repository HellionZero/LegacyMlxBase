/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:13:21 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/30 14:03:31 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	player_to_frect(t_dcoord pos, float radius, t_frect *out)
{
	if (!out)
		return ;
	out->width = radius * 2.0f;
	out->height = radius * 2.0f;
	out->x = (float)(pos.x - out->width / 2.0f);
	out->y = (float)(pos.y - out->height / 2.0f);
}

void	frect_sample_point(const t_frect *r, int i, int j,
			t_dcoord *out)
{
	if (!r || !out)
		return ;
	out->x = (double)r->x + (i / 2.0) * (double)r->width;
	out->y = (double)r->y + (j / 2.0) * (double)r->height;
}

int	frect_collides_map(t_map *map, const t_frect *r, int i)
{
	t_dcoord	sample;
	t_icoord	g;
	int			j;

	if (!map || !map->grid || !r)
		return (1);
	while (i <= 2)
	{
		j = 0;
		while (j <= 2)
		{
			frect_sample_point(r, i, j, &sample);
			g.x = (int)floor(sample.x);
			g.y = (int)floor(sample.y);
			if (g.x < 0 || g.y < 0 || g.x >= map->dim.width
				|| g.y >= map->dim.height)
				return (1);
			if (map->grid[g.y][g.x] == '1')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	rect_collides(t_map *map, t_dcoord pos, float radius)
{
	t_frect	r;

	player_to_frect(pos, radius, &r);
	return (frect_collides_map(map, &r, 0));
}
