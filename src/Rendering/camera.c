/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:22:30 by aurban            #+#    #+#             */
/*   Updated: 2023/11/21 21:50:20 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move_cam(t_param *p, int direction, long double move_amount)
{
	if (direction == MV_UP)
		p->oo_coordinate.i += (long double)p->h * move_amount;
	else if (direction == MV_DOWN)
		p->oo_coordinate.i -= (long double)p->h * move_amount;
	else if (direction == MV_RIGHT)
		p->oo_coordinate.r -= (long double)p->w * move_amount;
	else if (direction == MV_LEFT)
		p->oo_coordinate.r += (long double)p->w * move_amount;
}
