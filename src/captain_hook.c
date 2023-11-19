/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   captain_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:40:05 by aurban            #+#    #+#             */
/*   Updated: 2023/11/19 12:48:48 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define MV_RIGHT 2
#define MV_LEFT -2
#define MV_UP 1
#define MV_DOWN -1
#define MOVE_AMMOUNT 0.01

#define	SHIFT_AMMOUNT 15
#define MAGIC_COLOR 420

static void	move_cam(t_param *p, int direction)
{
	if (direction == MV_UP)
		p->img_origin.i += (long double)p->h * MOVE_AMMOUNT * p->zoom;
	else if (direction == MV_DOWN)
		p->img_origin.i -= (long double)p->h * MOVE_AMMOUNT * p->zoom;
	else if (direction == MV_RIGHT)
		p->img_origin.r -= (long double)p->w * MOVE_AMMOUNT * p->zoom;
	else if (direction == MV_LEFT)
		p->img_origin.r += (long double)p->w * MOVE_AMMOUNT * p->zoom;
	ft_image_update(p);
	ft_printf("Move Update Done\n");
}

static uint8_t	shift_color_change(uint8_t *channel, int direction)
{
	int	change;

	change = direction * SHIFT_AMMOUNT;
	if (change + *channel > 255)
		change = 255 - *channel;
	else if (change + *channel < 0)
		change = (int)(*channel) * -1;
	*channel += change;
	return (change);
}

static void	shift_color(t_param *p, int color, int direction)
{
	int	change;

	change = 0;
	if (color == MAGIC_COLOR)
	{
		if (direction == MV_UP)
			p->colors.magic += 5.0;
		else
			if (p->colors.magic - 5.0 > 0)
				p->colors.magic -= 5.0;
		change = 1;
	}
	else
	{
		if (color == SHIFT_RED)
			change = shift_color_change(&p->colors.red, direction);
		else if (color == SHIFT_GREEN)
			change = shift_color_change(&p->colors.green, direction);
		else if (color == SHIFT_BLUE)
			change = shift_color_change(&p->colors.blue, direction);
		ft_printf("NEW COLORS= r=%u  g=%u  b=%u\n", p->colors.red \
		,p->colors.green, p->colors.blue);
	}
	if (change)
		ft_image_update(p);
}

static void	cptn_hook_keys2(mlx_key_data_t keydata, t_param *p)
{
	if (keydata.key == MLX_KEY_R)
		shift_color(p, SHIFT_RED, MV_UP);
	else if (keydata.key == MLX_KEY_F)
		shift_color(p, SHIFT_RED, MV_DOWN);
	else if (keydata.key == MLX_KEY_T)
		shift_color(p, SHIFT_GREEN, MV_UP);
	else if (keydata.key == MLX_KEY_G)
		shift_color(p, SHIFT_GREEN, MV_DOWN);
	else if (keydata.key == MLX_KEY_Y)
		shift_color(p, SHIFT_BLUE, MV_UP);
	else if (keydata.key == MLX_KEY_H)
		shift_color(p, SHIFT_BLUE, MV_DOWN);
	else if (keydata.key == MLX_KEY_M)
		shift_color(p, MAGIC_COLOR, MV_UP);
	else if (keydata.key == MLX_KEY_N)
		shift_color(p, MAGIC_COLOR, MV_DOWN);
}

void	cptn_hook_keys(mlx_key_data_t keydata, void *param)
{
	t_param	*p;
	
	p = (t_param *) param;
	if (keydata.action == MLX_RELEASE)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(p->mlx);
	else if (keydata.key == MLX_KEY_RIGHT)
		move_cam(p, MV_RIGHT);
	else if (keydata.key == MLX_KEY_LEFT)
		move_cam(p, MV_LEFT);
	else if (keydata.key == MLX_KEY_UP)
		move_cam(p, MV_UP);
	else if (keydata.key == MLX_KEY_DOWN)
		move_cam(p, MV_DOWN);
	else
		cptn_hook_keys2(keydata, p);
}

void	cptn_hook_zoom(void *param)
{
	if (param)
		ft_printf("");
}