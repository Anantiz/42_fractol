/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:24:23 by aurban            #+#    #+#             */
/*   Updated: 2023/11/21 11:26:41 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	args_help(void);
int	error_invalid_set(char set);
int	error_invalid_constant(int error);
int	checkif_error(int error, t_param *p);

int	args_help(void)
{
	ft_printf("Parameters:"
		"\n\t(required)set=your_set     Fractal Sets:  'M'= Mandlebrot "
		"'J'= Julia"
		"\n\t(depends )const=set const  Fractal Const: xxixx (x are digits)"
		"\n\t\t  Some recommended constants: 0.285i0.01  0.285i0.013  "
		"-0,038088i0.9754633"
		"\n\t(optional)size=size        [baby, small, medium, large, big_chu"
		"ngus]  impacts rendering speed\n");
	return (0);
}

int	error_invalid_set(char set)
{
	ft_printf("ERROR: Invalid set argument, no valid set for '%c'\n", set);
	return (0);
}

int	error_invalid_constant(int error)
{
	if (error == -1)
		ft_printf("ERROR: No 'const' argument\n");
	else
	{
		ft_printf("ERROR: Could not convert argument 'const' into a valid"
			" Complex Number:\n"
			"\tArgument must be as follow |real_part'i'complex_part|\n"
			"\tExample: \"42i58\"   Real:42 Complex:58\n");
	}
	return (0);
}

int	checkif_error(int error, t_param *p)
{
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
