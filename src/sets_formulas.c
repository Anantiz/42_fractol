/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets_formulas.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:15:57 by aurban            #+#    #+#             */
/*   Updated: 2023/11/18 12:51:06 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define GREEN	0x00FF1CFF
#define CYAN	0x001C00FF
#define BLUE	0x0000CCFF
#define PURPLE	0x30046EFF
#define BLACK	0x000000FF
#define PINK	0xFFC0CBFF

/*
	Blue shift for faster infinity convergence
	Red  shift for slower infinity convergence
*/
static unsigned int get_color(unsigned int n)
{
	unsigned int	color;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	float			normalized_n;

	if (n == MAX_ITER)
	{
		return (BLACK);
	}
	normalized_n = (float)n / MAX_ITER;
	red = (unsigned int)(normalized_n * 180);
	green = (unsigned int)(normalized_n * 67);
	blue = (unsigned int)(normalized_n * 200);
	color = (red << 24) + (green << 16) + (blue << 8) + 255;
	return (color);
}

unsigned int	mandlebrot_set(t_i *c) // C is a constant based on pixel value, Z starts at 0
{
	unsigned int	n;
	long double		zr;
	t_i				z;

	z.r = 0;
	z.i = 0;
	n = 0;
	FILE *fd = fopen("log.txt", "a");
	fprintf(fd,"r=%LF  i=%LF\n",c->r, c->i);
	while (n < MAX_ITER)
	{
		if (((z.r * z.r) + (z.i * z.i)) > MAX_CONVERGE)
			break ;
		zr = z.r;
		z.r = (z.r * z.i) - (z.i * z.r) + c->r; // Z = Z^2 + C  
		z.i = (zr * z.i) + (z.i * zr) + c->i;
		n++;
	}
	fclose(fd);
	return (get_color(n));
}

unsigned int	julia_set(t_i *z, t_i *c) // C is a constant given as input, Z starts with the pixel
{
	unsigned int	n;
	long double		zr;

	n = 0;
	while (n < MAX_ITER)
	{
		if ((z->r * z->r + z->i * z->i) > MAX_CONVERGE)
			break ;
		zr = z->r;
		z->r = (z->r * z->i) - (z->i * z->r) + c->r;
		z->i = (zr * z->i) + (z->i * zr) + c->i;
		n++;
	}
	return (get_color(n));
}