/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   captain_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:40:05 by aurban            #+#    #+#             */
/*   Updated: 2023/11/18 18:28:24 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	cptn_hook_keys(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		
}

void	cptn_hook_zoom(void *param)
{
	if (param)
		ft_printf("");
}

void	cptn_hook_move_cam(void *param)
{
	if (param)
		ft_printf("");
}

void	cptn_hook_shift_color(void *param)
{
	if (param)
		ft_printf("");
}