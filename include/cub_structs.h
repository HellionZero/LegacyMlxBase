/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:35:12 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/17 16:14:47 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCTS_H
# define CUB_STRUCTS_H

typedef struct s_window t_window;
typedef struct s_game	t_game;

struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
};

struct s_game
{
	t_window	*window;
};

#endif