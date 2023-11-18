/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:24:23 by aurban            #+#    #+#             */
/*   Updated: 2023/11/18 12:27:05 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	args_help()
{
	ft_printf("Parameters:"
	"\n\t(required)set=\"your set\"     Fractal Set:  'M'= Mandlebrot "
	"'J'= Julia"
	"\n\t(depends )const=\"set const\"  Fractal Const: xxixx (x are digits)"
	"\n\t(optional)size=\"size\"        [baby, small, medium, large] impacts"
	" rendering speed\n");
	return (0);
}

int	error_invalid_set(char set)
{
	ft_printf("Invalid set argument, no valid set for '%c' or invalid"
	" constant\n", set);
	return (0);
}

int	error_invalid_constant(int error)
{
	if (error == -1)
	{
		ft_printf("Invalid Argument count or wrong position for constant\n");
		args_help();
	}
	else
	{
		ft_printf("Could not convert argument (set-constant) into a valid"
		" Complex Number:\n"
		"\tArgument must be as follow |real_part'i'complex_part|\n"
		"\tExample: \"42i58\"   Real:42 Complex:58\n")	;
	}
	return (0);
}