/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_validation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:56:05 by bmoreira          #+#    #+#             */
/*   Updated: 2026/05/07 15:39:35 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_VALIDATION_H
# define CUB_VALIDATION_H

/* ----------validation functions---------- */

/*verify if the elements present in the map are valid*/
int	is_valid_elements(t_map *map);

/*verify if the color identifier is valid (F or C)*/
int	is_valid_color(char *id);

/*verify if the RGB values are valid (3 values between 0 and 255)*/
int	is_valid_rgb(char **rgb);

/*verify if the texture identifier is valid (NO, SO, WE, EA)*/
int	is_valid_texture(char *id);

#endif