/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:39:54 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/20 15:42:08 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	init_timer(t_timer *timer)
{
	gettimeofday(&timer->last_time, NULL);
	timer->delta_time = 0.0f;
}

void	update_timer(t_timer *timer)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	timer->delta_time = (current_time.tv_sec - timer->last_time.tv_sec)
		+ (current_time.tv_usec - timer->last_time.tv_usec) / 1000000.0f;
	timer->last_time = current_time;
}
