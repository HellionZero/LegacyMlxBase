/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:05:28 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/20 15:14:30 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

t_icoord	calcule_delta(t_icoord start, t_icoord end)
{
	t_icoord	delta;

	if (end.x > start.x)
		delta.x = end.x - start.x;
	else
		delta.x = start.x - end.x;
	if (end.y > start.y)
		delta.y = end.y - start.y;
	else
		delta.y = start.y - end.y;
	return (delta);
}

t_icoord	calcule_step(t_icoord start, t_icoord end)
{
	t_icoord	step;

	if (start.x < end.x)
		step.x = 1;
	else
		step.x = -1;
	if (start.y < end.y)
		step.y = 1;
	else
		step.y = -1;
	return (step);
}
