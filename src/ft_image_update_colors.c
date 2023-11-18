/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_update_colors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:23:02 by aurban            #+#    #+#             */
/*   Updated: 2023/11/18 19:54:47 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_image_update_color(t_param *p, int color, uint8_t change)
{
	unsigned int	pixel_y;
	unsigned int	pixel_x;
	uint8_t			*chnl;
	uint8_t			p_color;

	p_color = *(&p->colors.red + (sizeof(uint8_t) * (color - 1)));
	pixel_y = 0;
	while (pixel_y < p->h)
	{
		pixel_x = 0;
		while (pixel_x < p->w)
		{
			chnl = &p->img->pixels[((pixel_y * p->h + pixel_x) * 4) + color];
			*chnl = ((*chnl ) * p_color) / (p_color + change);
			pixel_x++;
		}
		pixel_y++;
	}
	ft_printf("Coloring done\n");
}
