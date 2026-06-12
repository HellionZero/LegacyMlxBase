/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbara.drummond <barbara.drummond@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:55:19 by bmoreira          #+#    #+#             */
/*   Updated: 2026/05/09 23:55:32 by barbara.dru      ###   ########.fr       */
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

int	is_valid_map_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (!(line[i] == '0' || line[i] == '1' || line[i] == ' '
				|| line[i] == '\t' || line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'E' || line[i] == 'W' || line[i] == '\n'))
			return (0);
		i++;
	}
	return (1);
}
