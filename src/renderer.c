/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 08:52:52 by aurban            #+#    #+#             */
/*   Updated: 2023/11/18 12:45:00 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	map_pixel_to_point(t_i *pixel_pos, t_param *p)
{
	long double	r;
	long double	i;

	r = (pixel_pos->r - p->img_origin.r) * p->zoom * p->screen_resolution;
	i = (pixel_pos->i - p->img_origin.i) * p->zoom * p->screen_resolution;
	pixel_pos->i = i;
	pixel_pos->r = r;
}

int	ft_init_image(t_param *p)
{
	t_i				pixel_coordinates;
	unsigned int	pixel_x;
	unsigned int	pixel_y;
	unsigned int	color;

	//y 1:-1	x 1:-2
	/*
	0:0 will be middle of the image 2/3 right
	*/
	p->img_origin.r = p->w - (p->w / 3);
	p->img_origin.i = p->h / 2;
	printf("W=%u H=%u\n",p->w, p->h);
	printf("origin R=%LF\torigin I=%LF\n",p->img_origin.r, p->img_origin.i);
	color = 0;
	pixel_y = 0;
	while (pixel_y < p->h)
	{
		pixel_x = 0;
		while (pixel_x < p->w)
		{
			pixel_coordinates.r = pixel_x;
			pixel_coordinates.i = pixel_y;
			map_pixel_to_point(&pixel_coordinates, p);
			if (p->set == 'M')
				color = mandlebrot_set(&pixel_coordinates);
			else if (p->set == 'J')
				color = julia_set(&pixel_coordinates, &p->c);
			mlx_put_pixel(p->img, pixel_x, pixel_y, color);
			pixel_x++;
		}
		pixel_y++;
	}
	return (0);
}