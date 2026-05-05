/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:11:35 by bmoreira          #+#    #+#             */
/*   Updated: 2026/05/05 16:43:09 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static char	*normalize_texture_path(char *path)
{
	char	*normalized;
	int		fd;

	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		return (ft_strdup(path));
	}
	normalized = ft_strjoin("src/", path);
	fd = open(normalized, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		return (normalized);
	}
	free(normalized);
	return (ft_strdup(path));
}

static int	get_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static void	set_texture(t_map *map, char **element)
{
	char	*normalized;

	if (!ft_strcmp(element[0], "NO"))
	{
		normalized = normalize_texture_path(element[1]);
		map->north_path = normalized;
	}
	else if (!ft_strcmp(element[0], "SO"))
	{
		normalized = normalize_texture_path(element[1]);
		map->south_path = normalized;
	}
	else if (!ft_strcmp(element[0], "WE"))
	{
		normalized = normalize_texture_path(element[1]);
		map->west_path = normalized;
	}
	else if (!ft_strcmp(element[0], "EA"))
	{
		normalized = normalize_texture_path(element[1]);
		map->east_path = normalized;
	}
	ft_free_split(element);
}

static void	set_color(t_map *map, char **element)
{
	char	**rgb;

	rgb = ft_split(element[1], ',');
	if (is_valid_rgb(rgb))
	{
		if (!ft_strcmp(element[0], "F"))
			map->floor_color
				= get_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
		else if (!ft_strcmp(element[0], "C"))
			map->ceiling_color
				= get_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
		ft_free_split(rgb);
		ft_free_split(element);
	}
	else
	{
		ft_free_split(rgb);
		error_handler(map, element, INVALID_COLOR);
	}
}

void	parse_element(t_map *map, char *line)
{
	char	**element;
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n");
	free(line);
	if (!trimmed || trimmed[0] == '\0')
	{
		free(trimmed);
		return ;
	}
	element = ft_split(trimmed, ' ');
	free(trimmed);
	if (ft_split_size(element) != 2)
		error_handler(map, element, INVALID_ELEMENT);
	if (is_valid_texture(element[0]))
		set_texture(map, element);
	else if (is_valid_color(element[0]))
		set_color(map, element);
	else
		error_handler(map, element, INVALID_ELEMENT);
}
