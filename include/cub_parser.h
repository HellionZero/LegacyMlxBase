/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 20:17:59 by bmoreira          #+#    #+#             */
/*   Updated: 2026/05/05 16:03:19 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_PARSER_H
# define CUB_PARSER_H

# include "cub_structs.h"
# include "cub_validation.h"
# include <fcntl.h>

typedef enum e_exit_code
{
	READ_FILE,
	INVALID_ELEMENT,
	INVALID_COLOR,
    JOIN_CONTENT,
}	t_exit_code;

void	error_handler(t_map *map, char **split, int exit_code);
void	free_map(t_map *map);
void	parse_element(t_map *map, char *line);
int		parse_map(t_map *map, char *file_name);
t_map	*init_map(void);

int		is_orientation_char(char c);
float	set_start_angle(char orientation);
int		count_map_rows(char **grid);
int		count_map_columns(char **grid);

#endif