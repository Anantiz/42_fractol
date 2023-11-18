/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets_formulas.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:15:57 by aurban            #+#    #+#             */
/*   Updated: 2023/11/18 18:19:12 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
	Blue shift for faster infinity convergence
	Red  shift for slower infinity convergence
*/
static unsigned int get_color(unsigned int n, t_colors *colors)
{
	unsigned int	color;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	float			normalized_n;

	if (n == MAX_ITER)
	{
		return (colors->void_color);
	}
	normalized_n = (float)n / (MAX_ITER / colors->magic);
	red = (unsigned int)(normalized_n * colors->red);
	green = (unsigned int)(normalized_n * colors->green);
	blue = (unsigned int)(normalized_n * colors->blue);
	color = (red << 24) + (green << 16) + (blue << 8) + 255;
	return (color);
}

/*
C is a constant based on pixel value, Z starts at 0
*/
unsigned int	mandlebrot_set(t_colors *colors, t_i *c)
{
	unsigned int	n;
	long double		zr;
	t_i				z;

	z.r = 0;
	z.i = 0;
	n = 0;
	//FILE *fd = fopen("log.txt", "a");
	//fprintf(fd,"r=%LF  i=%LF\n",c->r, c->i);
	while (n < MAX_ITER)
	{
		if (((z.r * z.r) + (z.i * z.i)) > MAX_CONVERGE)
			break ;
		zr = z.r;
		z.r = (z.r * z.r) - (z.i * z.i) + c->r; // R = r*r - i*i + c.r
		z.i = 2 * (zr * z.i) + c->i;  //  I = 2 * i*r + c.i
		n++;
	}
	//fclose(fd);
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
	while (n < MAX_ITER)
	{
		if ((z->r * z->r + z->i * z->i) > MAX_CONVERGE)
			break ;
		zr = z->r;
		z->r = (z->r * z->r) - (z->i * z->i) + c->r;
		z->i = 2 * (zr * z->i) + c->i;
		n++;
	}
	return (get_color(n, colors));
}
