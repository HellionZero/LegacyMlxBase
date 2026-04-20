/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eight_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:21:41 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/20 16:45:05 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	calculate_pivot_points(t_rectangle *rect)
{
	int	half_w;
	int	half_h;

	half_w = rect->dim.width / 2;
	half_h = rect->dim.height / 2;
	rect->points[TOP_LEFT] = (t_icoord){rect->pos.x, rect->pos.y};
	rect->points[TOP_CENTER] = (t_icoord){rect->pos.x + half_w, rect->pos.y};
	rect->points[TOP_RIGHT] = (t_icoord){rect->pos.x + rect->dim.width,
		rect->pos.y};
	rect->points[CENTER_LEFT] = (t_icoord){rect->pos.x, rect->pos.y + half_h};
	rect->points[CENTER] = (t_icoord){rect->pos.x + half_w,
		rect->pos.y + half_h};
	rect->points[CENTER_RIGHT] = (t_icoord){rect->pos.x + rect->dim.width,
		rect->pos.y + half_h};
	rect->points[BOTTOM_LEFT] = (t_icoord){rect->pos.x,
		rect->pos.y + rect->dim.height};
	rect->points[BOTTOM_CENTER] = (t_icoord){rect->pos.x + half_w,
		rect->pos.y + rect->dim.height};
	rect->points[BOTTOM_RIGHT] = (t_icoord){rect->pos.x + rect->dim.width,
		rect->pos.y + rect->dim.height};
}
