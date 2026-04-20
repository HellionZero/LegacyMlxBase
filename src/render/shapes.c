/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:48:15 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/20 15:18:17 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	draw_line(t_data *data, t_icoord start, t_icoord end, int color)
{
	t_icoord	delta;
	t_icoord	step;
	int			err;
	int			e2;

	delta = calcule_delta(start, end);
	step = calcule_step(start, end);
	err = delta.x - delta.y;
	while (1)
	{
		mlx_put_pixel(data, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 > -delta.y)
		{
			err -= delta.y;
			start.x += step.x;
		}
		if (e2 < delta.x)
		{
			err += delta.x;
			start.y += step.y;
		}
	}
}

void	draw_rectangle(t_data *data, t_icoord pos, t_dim dim, int color)
{
	int	i;
	int	j;

	j = pos.y;
	while (j < pos.y + dim.height)
	{
		i = pos.x;
		while (i < pos.x + dim.width)
		{
			mlx_put_pixel(data, i, j, color);
			i++;
		}
		j++;
	}
}
