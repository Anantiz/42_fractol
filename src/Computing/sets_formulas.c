/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets_formulas.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:15:57 by aurban            #+#    #+#             */
/*   Updated: 2023/11/22 00:36:29 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	mandlebrot_set(t_colors *colors, t_i *c);
unsigned int	julia_set(t_colors *colors, t_i *z, t_i *c);

/*
C is a constant based on pixel value, Z starts at 0
*/
unsigned int	mandlebrot_set(t_colors *colors, t_i *c)
{
	unsigned int	n;
	long double		zr;
	t_i				z;

	z.r = 0.0;
	z.i = 0.0;
	n = 0;
	while (n < colors->max_iter)
	{
		if (((z.r * z.r) + (z.i * z.i)) > MAX_CONVERGE)
			break ;
		zr = z.r;
		z.r = (z.r * z.r) - (z.i * z.i) + c->r;
		z.i = 2 * (zr * z.i) + c->i;
		n++;
	}
	return (get_color(n, colors));
}

unsigned int	celtic_set(t_colors *colors, t_i *c)
{
	unsigned int	n;
	long double		zr;
	t_i				z;

	z.r = 0.0;
	z.i = 0.0;
	n = 0;
	while (n < colors->max_iter)
	{
		if (((z.r * z.r) + (z.i * z.i)) > MAX_CONVERGE)
			break ;
		zr = z.r;
		z.r = ft_abs((z.r * z.r) - (z.i * z.i)) + c->r;
		z.i = 2 * (zr * z.i) + c->i;
		n++;
	}
	return (get_color(n, colors));
}

/*
C is a constant given as input, Z starts with the pixel
*/
unsigned int	julia_set(t_colors *colors, t_i *z, t_i *c)
{
	unsigned int	n;
	long double		zr;

	n = 0;
	while (n < colors->max_iter)
	{
		if ((z->r * z->r + z->i * z->i) > colors->max_iter)
			break ;
		zr = z->r;
		z->r = (z->r * z->r) - (z->i * z->i) + c->r;
		z->i = 2 * (zr * z->i) + c->i;
		n++;
	}
	return (get_color(n, colors));
}
