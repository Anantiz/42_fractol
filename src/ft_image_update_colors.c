/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_update_colors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:23:02 by aurban            #+#    #+#             */
/*   Updated: 2023/11/19 12:02:30 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_image_update_color(t_param *p, int color, int change)
{
	unsigned int	pixel_y;
	unsigned int	pixel_x;
	uint8_t			*chnl;
	uint8_t			color_value;

	color_value = *(&p->colors.red + (sizeof(uint8_t) * (color)));
	pixel_y = 0;
	while (pixel_y < p->h)
	{
		pixel_x = 0;
		while (pixel_x < p->w)
		{
			chnl = &p->img->pixels[((pixel_y * p->w + pixel_x) * 4) + color];
			*chnl = (uint8_t)((((float)(*chnl ) / ((float)color_value + change + 1))) * (float)color_value);
			pixel_x++;
		}
		pixel_y++;
	}
	ft_printf("Coloring done\n");
}
