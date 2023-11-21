/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:52:55 by aurban            #+#    #+#             */
/*   Updated: 2023/11/19 12:18:43 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_atoz(t_i *z, char *str)
{
	if (z == NULL)
		return (69);
	if (!str)
		return (-1);
	z->r = ft_atoldb(str);
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str) || *str == '.' || *str == ',')
		str++;
	if (*str++ != 'i')
		return (-2);
	z->i = ft_atoldb(str);
	return (0);
}
