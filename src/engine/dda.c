/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:58:30 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/30 20:06:18 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	init_dda_variables(t_ray *ray, t_dcoord *rd,
			t_icoord *rmap, t_dcoord *delta_dist)
{
	rd->x = ray->fdir.x;
	rd->y = ray->fdir.y;
	rmap->x = (int)floor(ray->fpos.x);
	rmap->y = (int)floor(ray->fpos.y);
	if (rd->x == 0.0)
		delta_dist->x = 1e-30;
	else
		delta_dist->x = fabs(1.0 / rd->x);
	if (rd->y == 0.0)
		delta_dist->y = 1e-30;
	else
		delta_dist->y = fabs(1.0 / rd->y);
}
