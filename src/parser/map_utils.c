/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 14:25:05 by lsarraci          #+#    #+#             */
/*   Updated: 2026/05/01 20:00:57 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	count_map_rows(char **grid)
{
	int	count;

	count = 0;
	if (!grid)
		return (0);
	while (grid[count])
		count++;
	return (count);
}

int	count_map_columns(char **grid)
{
	int	count;

	count = 0;
	if (!grid || !grid[0])
		return (0);
	while (grid[0][count])
		count++;
	return (count);
}

int	is_orientation_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
