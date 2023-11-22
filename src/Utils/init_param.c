/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:50:07 by aurban            #+#    #+#             */
/*   Updated: 2023/11/22 00:37:51 by aurban           ###   ########.fr       */
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

#define RED_HUE 0xda
#define GREEN_HUE 0x44
#define BLUE_HUE 0x00
#define VOID_COLOR 0x000000FF

int	init_param(char **argv, int argc, t_param *p);
int	init_size(char *str, t_param *p);
int	init_set(char *str, t_param *p);
int	init_const(char *str, t_param *p);

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
	p->colors.red = RED_HUE;
	p->colors.green = GREEN_HUE;
	p->colors.blue = BLUE_HUE;
	p->colors.void_color = VOID_COLOR;
	p->colors.magic = DEFAULT_MAGIC;
	p->colors.max_iter = MAX_ITER;
	p->colors.bg_color = 1;
	p->zoom_count = 0;
	return (error);
}

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
int	init_size(char *str, t_param *p)
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
	p->win_resolution = (long double)1 / (p->h / 2.5);
	return (100);
}

/*
Init constants for the sets requiring it
*/
int	init_const(char *str, t_param *p)
{
	int	error;

	error = ft_atoz(&p->c, str);
	if (error)
	{
		p->set = '0';
		error_invalid_constant(error);
		return (-1000);
	}
	return (10);
}

/*
initialize whcih set to use
*/
int	init_set(char *str, t_param *p)
{
	if (*str == 'M' || *str == 'm')
		p->set = 'M';
	else if (*str == 'C' || *str == 'c')
		p->set = 'C';
	else if (*str == 'W' || *str == 'w')
		p->set = 'W';
	else if (*str == 'J' || *str == 'j')
		p->set = 'J';
	else
	{
		p->set = '0';
		error_invalid_set(*str);
		return (-1000);
	}
	return (0);
}
