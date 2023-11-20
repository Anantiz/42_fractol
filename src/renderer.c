/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 08:52:52 by aurban            #+#    #+#             */
/*   Updated: 2023/11/20 18:49:50 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	map_pixel_to_point(t_i *pixel_pos, t_param *p)
{
	long double	r;
	long double	i;

	r = (pixel_pos->r - p->img_origin.r) * p->zoom * p->win_resolution;
	i = (pixel_pos->i - p->img_origin.i) * p->zoom * p->win_resolution;
	pixel_pos->i = i;
	pixel_pos->r = r;
}

static void	ft_image_update_helper2(t_param *p, unsigned int pixel_y)
{
	t_i				pixel_coordinates;
	unsigned int	pixel_x;
	unsigned int	color;

	pixel_x = 0;
	while (pixel_x < p->w)
	{
		pixel_coordinates.r = pixel_x;
		pixel_coordinates.i = pixel_y;
		map_pixel_to_point(&pixel_coordinates, p);
		if (p->set == 'M')
			color = mandlebrot_set(&p->colors, &pixel_coordinates);
		else if (p->set == 'J')
			color = julia_set(&p->colors, &pixel_coordinates, &p->c);
		mlx_put_pixel(p->img, pixel_x, pixel_y, color);
		pixel_x++;
	}
}

int	ft_image_update(t_param *p)
{
	unsigned int	pixel_y;

	if (!p->img)
		return (-1);
	pixel_y = 0;
	while (pixel_y < p->h)
	{
		ft_image_update_helper2(p, pixel_y);
		pixel_y++;
	}
	return (0);
}
