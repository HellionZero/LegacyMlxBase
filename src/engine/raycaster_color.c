/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 20:22:15 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/04 15:40:27 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

unsigned int	color_to_hex(t_color color)
{
	return ((color.red << 16) | (color.green << 8) | color.blue);
}

t_color	hex_to_color(unsigned int hex)
{
	t_color	color;

	color.red = (hex >> 16) & 0xFF;
	color.green = (hex >> 8) & 0xFF;
	color.blue = hex & 0xFF;
	return (color);
}

t_color	apply_shade(t_color color, float shade)
{
	t_color	result;

	result.red = (unsigned int)fminf(255.0f, color.red * shade + 0.5f);
	result.green = (unsigned int)fminf(255.0f, color.green * shade + 0.5f);
	result.blue = (unsigned int)fminf(255.0f, color.blue * shade + 0.5f);
	return (result);
}

t_color	apply_side_darkening(t_color color, int side)
{
	if (side == 1)
		return (apply_shade(color, 0.6f));
	return (color);
}

float	calculate_shade_factor(float distance, float shadow_k,
			float light_intensity)
{
	float	shade;

	shade = expf(-distance * shadow_k);
	shade *= light_intensity;
	if (shade < 0.0f)
		shade = 0.0f;
	return (shade);
}
