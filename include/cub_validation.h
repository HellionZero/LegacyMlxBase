/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_validation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:56:05 by bmoreira          #+#    #+#             */
/*   Updated: 2026/05/04 17:45:22 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_VALIDATION_H
# define CUB_VALIDATION_H

int	is_valid_elements(t_map *map);
int	is_valid_color(char *id);
int	is_valid_rgb(char **rgb);
int	is_valid_texture(char *id);

#endif