/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   captain_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:40:05 by aurban            #+#    #+#             */
/*   Updated: 2023/11/18 19:33:13 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define MV_RIGHT 2
#define MV_LEFT -2
#define MV_UP 1
#define MV_DOWN -1
#define MOVE_AMMOUNT 0.25

#define	SHIFT_AMMOUNT 15

static void	move_cam(t_param *p, int direction)
{
	if (direction == MV_UP)
		p->img_origin.i += MOVE_AMMOUNT * p->zoom;
	else if (direction == MV_DOWN)
		p->img_origin.i -= MOVE_AMMOUNT * p->zoom;
	else if (direction == MV_RIGHT)
		p->img_origin.r -= MOVE_AMMOUNT * p->zoom;
	else if (direction == MV_LEFT)
		p->img_origin.r += MOVE_AMMOUNT * p->zoom;
	ft_image_update(p);
}

static void	shift_color(t_param *p, int color, int direction)
{
	if (color == SHIFT_RED)
		p->colors.red += SHIFT_AMMOUNT * direction;
	ft_image_update_color(p, color, SHIFT_AMMOUNT * direction);
}
		
void	cptn_hook_keys(mlx_key_data_t keydata, void *param)
{
	t_param	*p;
	
	p = (t_param *) param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_terminate(p->mlx);
	else if (keydata.key == MLX_KEY_RIGHT)
		move_cam(p, MV_RIGHT);
	else if (keydata.key == MLX_KEY_LEFT)
		move_cam(p, MV_LEFT);
	else if (keydata.key == MLX_KEY_UP)
		move_cam(p, MV_UP);
	else if (keydata.key == MLX_KEY_DOWN)
		move_cam(p, MV_UP);
	else if (keydata.key == MLX_KEY_R)
		shift_color(p, SHIFT_RED, MV_UP);
	else if (keydata.key == MLX_KEY_F)
		shift_color(p, SHIFT_RED, MV_DOWN);
}

void	cptn_hook_zoom(void *param)
{
	if (param)
		ft_printf("");
}