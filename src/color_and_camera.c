/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_and_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:54:02 by aurban            #+#    #+#             */
/*   Updated: 2023/11/20 19:01:15 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
	Blue shift for faster infinity convergence
	Red  shift for slower infinity convergence
*/
unsigned int	get_color(unsigned int n, t_colors *colors)
{
	unsigned int	color;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	float			normalized_n;

	if (n == colors->max_iter)
	{
		return (colors->void_color);
	}
	normalized_n = (float)n / ((float)colors->max_iter / colors->magic + 0.001);
	red = (unsigned int)(normalized_n * colors->red);
	green = (unsigned int)(normalized_n * colors->green);
	blue = (unsigned int)(1 - normalized_n * colors->blue);
	color = (red << 24) + (green << 16) + (blue << 8) + 255;
	return (color);
}

static int	shift_color_change(uint8_t *channel, int direction)
{
	int	change;

	change = direction * SHIFT_AMMOUNT;
	if (change + *channel > 255)
		change = 255 - *channel;
	else if (change + *channel < 0)
		change = ((int)(*channel)) * (-1);
	*channel += change;
	return (change);
}

void	shift_color(t_param *p, int color, int direction, float ammount)
{
	int	change;

	change = 0;
	if (color == MAGIC_COLOR)
	{
		if (direction == MV_UP && 0 == change++)
			p->colors.magic += DEFAULT_MAGIC * ammount;
		else
			if (p->colors.magic - DEFAULT_MAGIC > 0)
				p->colors.magic -= DEFAULT_MAGIC * ammount;
	}
	else
	{
		if (color == SHIFT_RED)
			change = shift_color_change(&p->colors.red, direction);
		else if (color == SHIFT_GREEN)
			change = shift_color_change(&p->colors.green, direction);
		else if (color == SHIFT_BLUE)
			change = shift_color_change(&p->colors.blue, direction);
		ft_printf("NEW COLORS= r=%u  g=%u  b=%u\n", p->colors.red \
		, p->colors.green, p->colors.blue);
	}
}

void	move_cam(t_param *p, int direction, long double move_amount)
{
	if (direction == MV_UP)
		p->img_origin.i += (long double)p->h * move_amount \
		* (p->zoom / p->zoom * 4);
	else if (direction == MV_DOWN)
		p->img_origin.i -= (long double)p->h * move_amount * \
		(p->zoom / p->zoom * 4);
	else if (direction == MV_RIGHT)
		p->img_origin.r -= (long double)p->w * move_amount * \
		(p->zoom / p->zoom * 4);
	else if (direction == MV_LEFT)
		p->img_origin.r += (long double)p->w * move_amount * \
		(p->zoom / p->zoom * 4);
}
