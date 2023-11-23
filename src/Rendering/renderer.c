/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 08:52:52 by aurban            #+#    #+#             */
/*   Updated: 2023/11/22 00:55:36 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			ft_image_update(t_param *p);
static void	ft_image_update_helper2(t_param *p, unsigned int pixel_y);
void		map_pixel_to_point(t_i *pixel_pos, t_param *p);

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
		else if (p->set == 'C')
			color = celtic_set(&p->colors, &pixel_coordinates);
		else if (p->set == 'W')
		{
			p->c.r = pixel_coordinates.i + 0.1;
			p->c.i = pixel_coordinates.r - 0.1;
			color = julia_set(&p->colors, &pixel_coordinates, &p->c);
		}
		else if (p->set == 'J')
			color = julia_set(&p->colors, &pixel_coordinates, &p->c);
		mlx_put_pixel(p->img, pixel_x, pixel_y, color);
		pixel_x++;
	}
}

void	map_pixel_to_point(t_i *pixel_pos, t_param *p)
{
	long double	r;
	long double	i;

	r = (pixel_pos->r - p->oo_coordinate.r) * p->win_resolution * \
		(pow(ZOOM_AMMOUNT, p->zoom_count));
	i = (pixel_pos->i - p->oo_coordinate.i) * p->win_resolution * \
		(pow(ZOOM_AMMOUNT, p->zoom_count));
	pixel_pos->i = i;
	pixel_pos->r = r;
}

void	map_point_to_pixel(t_i *point, t_param *p)
{
	long double	r;
	long double	i;

	r = (point->r / (p->win_resolution * (pow(ZOOM_AMMOUNT, p->zoom_count)))) \
		+ p->oo_coordinate.r;
	i = (point->i / (p->win_resolution * (pow(ZOOM_AMMOUNT, p->zoom_count)))) \
		+ p->oo_coordinate.i;
	point->r = r;
	point->i = i;
}
