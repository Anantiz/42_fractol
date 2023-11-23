/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:22:30 by aurban            #+#    #+#             */
/*   Updated: 2023/11/21 23:42:08 by aurban           ###   ########.fr       */
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

void	cptn_hook_resize(int width, int height, void *param)
{
	t_param	*p;

	p = (t_param *)param;
	p->w = width;
	p->h = height;
	p->win_resolution = (long double)1.0 / (p->h / 2.5);
	ft_printf("Start resizing\t");
	mlx_delete_image(p->mlx, p->img);
	p->img = mlx_new_image(p->mlx, p->w, p->h);
	if (!p->img)
		p->img = NULL;
	if (mlx_image_to_window(p->mlx, p->img, 0, 0) < 0)
		p->img = NULL;
	ft_get_image_origin(&p->oo_coordinate, p);
	ft_printf("(I'm not dead)\t");
	ft_image_update(p);
	ft_printf("DONE\n");
}
