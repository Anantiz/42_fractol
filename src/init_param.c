/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:50:07 by aurban            #+#    #+#             */
/*   Updated: 2023/11/19 12:51:58 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


#define WIN_BABYX 320
#define WIN_BABYY 180
#define WIN_SMALLX 854
#define WIN_SMALLY 480
#define WIN_MEDIUMX 1600
#define WIN_MEDIUMY 900
#define WIN_LARGEX 2432
#define WIN_LARGEY 1368
#define WIN_BIGCHUNGUSX 3840
#define WIN_BIGCHUNGUSY 2160

#define RED_HUE 219
#define GREEN_HUE 67
#define BLUE_HUE 165
#define VOID_COLOR 0x000000FF


static void	init_size_helper(char *str, t_param *p)
{
	if (!ft_strncmp(str, "baby", 6))
	{
		p->w = WIN_BABYX;
		p->h = WIN_BABYY;
	}
}

/*
Predefined size, all are 16:9 for ease of display.
The origin r0:i0 of the fractal will be excentric from the image
*/
static int	init_size(char *str, t_param *p)
{
	p->w = WIN_SMALLX;
	p->h = WIN_SMALLY;
	if (str)
	{
		if (!ft_strncmp(str, "medium", 6))
		{
			p->w = WIN_MEDIUMX;
			p->h = WIN_MEDIUMY;
		}
		else if (!ft_strncmp(str, "large", 5))
		{
			p->w = WIN_LARGEX;
			p->h = WIN_LARGEY;
		}
		else if (!ft_strncmp(str, "big_chungus", 11))
		{		
			p->w = WIN_BIGCHUNGUSX;
			p->h = WIN_BIGCHUNGUSY;			
		}
		else
			init_size_helper(str, p);
	}
	p->screen_resolution = (long double)1 / (p->h / 2.5);
	return (100);
}
/*
Init constants for the sets requiring it
*/
static int	init_const(char *str, t_param *p)
{
	int	error;
	
	error = ft_atoz(&p->c, str);
	printf("error=%i  str=%s\n", error, str);
	if (error)
	{
		p->set = '0';
		error_invalid_constant(error);
		return (-1000);
	}
	printf("Const r=%LF  i=%LF\n",p->c.r, p->c.i);
	return (10);
}
/*
initialize whcih set to use
*/
static int	init_set(char *str, t_param *p)
{
	if (*str == 'M' || *str == 'm') // Mandlebrot
		p->set = 'M';
	else if (*str == 'J' || *str == 'j') // Julia
		p->set = 'J';
	else
	{
		p->set = '0';
		error_invalid_set(*str);
		return (-1000);
	}
	return (0);
}

static int	checkif_error(int error, t_param *p)
{
	printf("error=%d", error);
	if (error < 0)
		return (error);
	if (error < 100 && error >= 0)
		error += init_size(NULL, p);
	error -= 100;
	if (p->set == 'J' || error >= 10)
	{
		if (error >= 10)
			error -= 10;
		else
			init_const(NULL, p);
	}
	if (p->set == '0')
		error -= 1000;
	return (error);
}

/*
set  =  Fractal Set:  'M'= Mandlebrot 'J'= Julia"
const=  Fractal Const: xxixx (x are digits)"
size =  [baby, small, medium, large] impacts rendering speed\n");
*/
int	init_param(char **argv, int argc, t_param *p)
{
	int	error;

	error = 0;
	p->set = '0';
	while (argc-- > 1)
	{
		if (!ft_strncmp(argv[argc], "set=", 4))
			error += init_set(&argv[argc][4], p);
		else if (!ft_strncmp(argv[argc], "const=", 6))
			error += init_const(&argv[argc][6], p);
		else if (!ft_strncmp(argv[argc], "size=", 5))
			error += init_size(&argv[argc][5], p);
	}
	error = checkif_error(error, p);
	p->zoom = 1.0;
	p->colors.red = RED_HUE;
	p->colors.green = GREEN_HUE;
	p->colors.blue = BLUE_HUE;
	p->colors.void_color = VOID_COLOR;
	p->colors.magic = 2.0;
	return (error);
}
