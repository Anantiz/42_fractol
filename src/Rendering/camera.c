/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:22:30 by aurban            #+#    #+#             */
/*   Updated: 2023/11/21 11:22:59 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move_cam(t_param *p, int direction, long double move_amount)
{
	if (direction == MV_UP)
		p->img_origin.i += (long double)p->h * move_amount \
		* (p->zoom / p->zoom * 4);
	else if (direction == MV_DOWN)
		p->img_origin.i -= (long double)p->h * move_amount * \
		(p->zoom / p->zoom * 4);
	else if (direction == MV_RIGHT)
		p->img_origin.r -= (long double)p->w * move_amount * \
		(p->zoom / p->zoom * 4);
	else if (direction == MV_LEFT)
		p->img_origin.r += (long double)p->w * move_amount * \
		(p->zoom / p->zoom * 4);
}