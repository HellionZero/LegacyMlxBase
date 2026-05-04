/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:09:40 by lsarraci          #+#    #+#             */
/*   Updated: 2026/04/20 18:04:49 by lsarraci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static t_image	*destroy_texture_and_exit(void *mlx_ptr, t_image *texture)
{
	remove_texture(mlx_ptr, texture);
	ft_putstr_fd("Failed to load texture\n", 2);
	return (NULL);
}

t_image	*load_texture(void *mlx_ptr, char *path)
{
	t_image	*texture;

	texture = malloc(sizeof(t_image));
	if (!texture)
		return (NULL);
	texture->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path,
			&texture->dim.width, &texture->dim.height);
	if (!texture->img_ptr)
	{
		free(texture);
		return (NULL);
	}
	texture->addr = mlx_get_data_addr(texture->img_ptr,
			&texture->data.bits_per_pixel,
			&texture->data.line_length, &texture->data.endian);
	if (!texture->addr)
		return (destroy_texture_and_exit(mlx_ptr, texture));
	texture->path = ft_strdup(path);
	if (!texture->path)
		return (destroy_texture_and_exit(mlx_ptr, texture));
	return (texture);
}

void	render_texture(t_data *data, t_image *texture, t_icoord pos)
{
	int	x;
	int	y;
	int	color;

	if (!data || !texture || !texture->img_ptr)
		return ;
	y = 0;
	while (y < texture->dim.height)
	{
		x = 0;
		while (x < texture->dim.width)
		{
			color = *(unsigned int *)(texture->addr
					+ (y * texture->data.line_length + x
						* (texture->data.bits_per_pixel / 8)));
			if ((color & 0xFF000000) != 0)
				mlx_put_pixel(data, pos.x + x, pos.y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_textured_rectangle(t_data *data, t_icoord pos, t_dim dim,
			t_image *texture)
{
	int		x;
	int		y;
	int		color;
	int		tex_x;
	int		tex_y;

	if (!data || !texture || !texture->img_ptr)
		return ;
	y = 0;
	while (y < dim.height)
	{
		x = 0;
		while (x < dim.width)
		{
			tex_x = (x * texture->dim.width) / dim.width;
			tex_y = (y * texture->dim.height) / dim.height;
			color = *(unsigned int *)(texture->addr
					+ (tex_y * texture->data.line_length + tex_x
						* (texture->data.bits_per_pixel / 8)));
			mlx_put_pixel(data, pos.x + x, pos.y + y, color);
			x++;
		}
		y++;
	}
}

void	remove_texture(void *mlx_ptr, t_image *texture)
{
	if (texture)
	{
		if (texture->img_ptr)
			mlx_destroy_image(mlx_ptr, texture->img_ptr);
		if (texture->path)
			free(texture->path);
		free(texture);
	}
}
