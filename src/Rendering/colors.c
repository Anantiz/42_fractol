/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:54:02 by aurban            #+#    #+#             */
/*   Updated: 2023/11/22 01:05:36 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	get_color(unsigned int n, t_colors *colors);
void			inverse_bg_color(t_param *p);

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
	if (colors->bg_color == 1)
		blue = (unsigned int)(1 - normalized_n * colors->blue);
	else
		blue = (unsigned int)(normalized_n * colors->blue);
	color = (red << 24) + (green << 16) + (blue << 8) + 255;
	return (color);
}

void	inverse_bg_color(t_param *p)
{
	p->colors.bg_color *= -1;
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

static int	shift_color_magic(t_param *p, int dir, float ammount)
{
	if (dir == MV_UP)
		p->colors.magic += ammount;
	else
	{
		if (p->colors.magic - ammount > 1.5)
			p->colors.magic -= ammount;
		else
			p->colors.magic = 1.5;
	}
	return (1);
}

void	shift_color(t_param *p, int color, int dir, float ammount)
{
	if (color == MAGIC_COLOR)
		shift_color_magic(p, dir, ammount);
	else
	{
		if (color == SHIFT_RED)
			shift_color_change(&p->colors.red, dir);
		else if (color == SHIFT_GREEN)
			shift_color_change(&p->colors.green, dir);
		else if (color == SHIFT_BLUE)
			shift_color_change(&p->colors.blue, dir);
		ft_printf("NEW COLORS= r=%u  g=%u  b=%u\n", p->colors.red \
		, p->colors.green, p->colors.blue);
	}
}
