/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:04:29 by aurban            #+#    #+#             */
/*   Updated: 2023/11/19 11:00:33 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_get_image_origin(t_param *p)
{
	if (p->set == 'M')
	{
		p->img_origin.r = p->w - (p->w / 3);
		p->img_origin.i = p->h / 2;
	}
	else if (p->set == 'J')
	{
		p->img_origin.r = p->w / 2;
		p->img_origin.i = p->h / 2;
	}
}

int	generate_fractal(t_param *p)
{
	p->mlx = mlx_init(p->w, p->h, "Fract'ol", true); // Create window
	if (!p->mlx)
		return (-1);
	p->img = mlx_new_image(p->mlx, p->w, p->h); // Create Image
	if (!p->img)
		return (-2);
	if (mlx_image_to_window(p->mlx, p->img, 0, 0) < 0) // Enable display
		return (-3);
	ft_get_image_origin(p);
	ft_image_update(p);
	ft_printf("Init done\n");
	mlx_key_hook(p->mlx, cptn_hook_keys, p);
	mlx_loop(p->mlx);
	if (p->mlx)
		mlx_terminate(p->mlx);
	return (0);
}
