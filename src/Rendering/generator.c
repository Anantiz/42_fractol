/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:04:29 by aurban            #+#    #+#             */
/*   Updated: 2023/11/22 00:37:03 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		generate_fractal(t_param *p);
void	ft_get_image_origin(t_i *point, t_param *p);

int	generate_fractal(t_param *p)
{
	p->mlx = mlx_init(p->w, p->h, "Fract'ol", true);
	if (!p->mlx)
		return (-1);
	p->img = mlx_new_image(p->mlx, p->w, p->h);
	if (!p->img)
		return (-2);
	if (mlx_image_to_window(p->mlx, p->img, 0, 0) < 0)
		return (-3);
	ft_get_image_origin(&p->oo_coordinate, p);
	ft_image_update(p);
	mlx_key_hook(p->mlx, cptn_hook_keys, p);
	mlx_scroll_hook(p->mlx, cptn_hook_scroll, p);
	mlx_resize_hook(p->mlx, cptn_hook_resize, p);
	mlx_loop(p->mlx);
	if (p->mlx)
		mlx_terminate(p->mlx);
	return (0);
}

void	ft_get_image_origin(t_i *point, t_param *p)
{
	if (p->set == 'M' || p->set == 'C')
	{
		point->r = p->w - (p->w / 3);
		point->i = p->h / 2;
	}
	else if (p->set == 'J')
	{
		point->r = p->w / 2;
		point->i = p->h / 2;
	}
	else
	{
		point->r = p->w / 2;
		point->i = p->h / 2;
	}
}
