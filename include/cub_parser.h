/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 20:17:59 by bmoreira          #+#    #+#             */
/*   Updated: 2026/05/07 15:56:28 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_PARSER_H
# define CUB_PARSER_H

# include "cub_structs.h"
# include "cub_validation.h"
# include <fcntl.h>

/* exit codes for error handling */
typedef enum e_exit_code	t_exit_code;

enum e_exit_code
{
	READ_FILE,
	INVALID_ELEMENT,
	INVALID_COLOR,
	JOIN_CONTENT,
}	;

/* PARSER BASIC FUNCTIONS */

/* free the map if the map exists, print the error message and exit */
void	error_handler(t_map *map, char **split, int exit_code);

/* free each field of the map if the map exists */
void	free_map(t_map *map);

/* parse a line of the map file and update the map struct accordingly.
it looks for specific elements and updates the map fields, and set 
the colors and the normalized textures
(paths without the orientation characters) */
void	parse_element(t_map *map, char *line);

/* parse the map file and initialize the map struct.
it checks each line to know where are the config elements 
and the map line. */
int		parse_map(t_map *map, char *file_name);

/* parse the grid of the map file */
void	parse_grid(t_map *map, int fd, char *line);

/*set the initial values for the map struct */
t_map	*init_map(void);

/* -------------helper functions for parsing ----------------*/

/* verify if the character is an orientation character (N, S, E, W) */
int		is_orientation_char(char c);

/* set the initial angle for the player based on the orientation.
it uses the trigonometric circle values. */
float	set_start_angle(char orientation);

/*count the number of rows and columns in the map grid, given
the grid as a 2D array of strings parsed as the grid */
int		count_map_rows(char **grid);
int		count_map_columns(char **grid);

#endif