/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atodb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:25:28 by aurban            #+#    #+#             */
/*   Updated: 2023/11/17 10:49:36 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long double	get_decimal(char *str)
{
	long double	n;
	long double	i;

	n = 0.0;
	i = 10;
	while (ft_isdigit((int)(*str)))
	{
		n += (1 / i) * ((*str) - '0');
		i *= 10;
		str++;
	}
	return (n);
}

long double	ft_atoldb(char *str)
{
	long double		n;	
	long long	left;

	n = 0.0;
	left = ft_atoll(str);
	n += (long double)left;
	while (ft_isdigit((int)(*str)) && !(*str == '.' || *str == ','))
		str++;
	if (*str && (*str == '.' || *str == ','))
		n += get_decimal((str + 1));
	return (n);
}
