/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:43:01 by aurban            #+#    #+#             */
/*   Updated: 2023/11/21 23:50:49 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	update_iter_count(t_param *p, int direction, float ammount)
{
	long double	dynamic;

	dynamic = 0.1 * (p->colors.max_iter * 1 / ammount);
	if (direction == MV_UP)
	{
		if (p->colors.max_iter + ammount < MAX_ITER_ALLOWED + dynamic)
			p->colors.max_iter += ammount + dynamic;
	}
	else
	{
		if (p->colors.max_iter > MAX_ITER + ammount + dynamic)
			p->colors.max_iter -= ammount + dynamic;
		else
			p->colors.max_iter = MAX_ITER;
	}
	if (p->colors.max_iter > MAX_ITER_ALLOWED)
		p->colors.max_iter = MAX_ITER_ALLOWED;
}
