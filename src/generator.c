/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:04:29 by aurban            #+#    #+#             */
/*   Updated: 2023/11/18 10:20:39 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	ft_init_image(p);
	printf("Init done\n");
	mlx_loop(p->mlx);
	return (0);
}