/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 20:09:00 by bmoreira          #+#    #+#             */
/*   Updated: 2026/05/05 16:54:31 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	map->north_texture = NULL;
	map->south_texture = NULL;
	map->west_texture = NULL;
	map->east_texture = NULL;
	map->grid = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
	return (map);
}

void	parse_grid(t_map *map, int fd, char *line)
{
	char	*buffer;
	char	*tmp;

	buffer = ft_strdup("");
	if (!buffer)
		error_handler(map, NULL, JOIN_CONTENT);
	while (line)
	{
		tmp = ft_strjoin(buffer, line);
		if (!tmp)
		{
			free(buffer);
			error_handler(map, NULL, JOIN_CONTENT);
		}
		free(buffer);
		buffer = tmp;
		free(line);
		line = get_next_line(fd);
	}
	map->grid = ft_split(buffer, '\n');
	map->dim.width = count_map_columns(map->grid);
	map->dim.height = count_map_rows(map->grid);
	free(buffer);
	close(fd);
}

static int	process_config_line(t_map *map, char *line)
{
	char	*trimmed;
	char	**parts;

	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed || trimmed[0] == '\0')
	{
		free(trimmed);
		free(line);
		return (2);
	}
	parts = ft_split(trimmed, ' ');
	free(trimmed);
	if (parts[0] && (is_valid_texture(parts[0]) || is_valid_color(parts[0])))
	{
		parse_element(map, line);
		ft_free_split(parts);
		return (0);
	}
	ft_free_split(parts);
	return (1);
}

int	parse_map(t_map *map, char *file_name)
{
	char	*line;
	int		fd;
	int		status;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_handler(map, NULL, READ_FILE);
	line = get_next_line(fd);
	while (line)
	{
		status = process_config_line(map, line);
		if (status == 2)
			line = get_next_line(fd);
		else if (status == 0)
			line = get_next_line(fd);
		else
		{
			parse_grid(map, fd, line);
			return (0);
		}
	}
	close(fd);
	return (0);
}
