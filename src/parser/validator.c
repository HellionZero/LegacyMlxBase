/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:55:19 by bmoreira          #+#    #+#             */
/*   Updated: 2026/05/05 16:36:24 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	is_valid_color(char *id)
{
	return (!ft_strcmp(id, "F")
		|| !ft_strcmp(id, "C"));
}

int	is_valid_elements(t_map *map)
{
	return (map->north_path
		&& map->south_path
		&& map->west_path
		&& map->east_path
		&& map->grid);
}

int	is_valid_rgb(char **rgb)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	if (ft_split_size(rgb) != 3)
		return (0);
	while (rgb[i])
	{
		num = ft_atoi(rgb[i]);
		if (num < 0 || num > 255)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_texture(char *id)
{
	return (!ft_strcmp(id, "NO")
		|| !ft_strcmp(id, "SO")
		|| !ft_strcmp(id, "WE")
		|| !ft_strcmp(id, "EA"));
}
