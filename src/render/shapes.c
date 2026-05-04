/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:48:15 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/20 17:04:54 by lsarraci         ###   ########.fr       */
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

t_rectangle	draw_rectangle(t_data *data, t_icoord pos, t_dim dim, int color)
{
	int			i;
	int			j;
	t_rectangle	rect;

	rect.pos = pos;
	rect.dim = dim;
	rect.color = color;
	calculate_pivot_points(&rect);
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
	return (rect);
}

void	draw_circle(t_data *data, t_icoord center, int radius, int color)
{
	int	x;
	int	y;
	int	err;

	x = radius;
	y = 0;
	err = 0;
	while (x >= y)
	{
		mlx_put_pixel(data, center.x + x, center.y + y, color);
		mlx_put_pixel(data, center.x + y, center.y + x, color);
		mlx_put_pixel(data, center.x - y, center.y + x, color);
		mlx_put_pixel(data, center.x - x, center.y + y, color);
		mlx_put_pixel(data, center.x - x, center.y - y, color);
		mlx_put_pixel(data, center.x - y, center.y - x, color);
		mlx_put_pixel(data, center.x + y, center.y - x, color);
		mlx_put_pixel(data, center.x + x, center.y - y, color);
		y++;
		err += 1 + 2 * y;
		if (2 * (err - x) + 1 > 0)
		{
			x--;
			err += 1 - 2 * x;
		}
	}
}

void	draw_polygon(t_data *data, t_icoord *points, int num_points, int color)
{
	int	i;

	if (num_points < 2)
		return ;
	i = 0;
	while (i < num_points)
	{
		draw_line(data, points[i], points[(i + 1) % num_points], color);
		i++;
	}
}
