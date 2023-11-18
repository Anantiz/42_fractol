/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:30:59 by aurban            #+#    #+#             */
/*   Updated: 2023/11/16 18:11:29 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		result;
	int		sign;

	result = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr && *nptr >= 48 && *nptr <= 57)
	{
		result *= 10;
		result += sign * (*nptr++ - 48);
	}
	return (result);
}

long long	ft_atoll(char *nptr)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr && *nptr >= 48 && *nptr <= 57)
	{
		result *= 10;
		result += sign * (*nptr++ - 48);
	}
	return (result);
}
